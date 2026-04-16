# efi-vuln: A Patch-Verified Dataset of UEFI Vulnerabilities

## Overview
efi-vuln contains 300 function-level C source snippets (150 vulnerable + 150 corresponding post-patch) derived from publicly disclosed UEFI firmware vulnerabilities. Samples are sourced from Binarly Research Team advisories (BRLY-*), the Damn Vulnerable UEFI educational series (BRLY-DVA-*), and the LogoFAIL vulnerability set (BRLY-LOGOFAIL-*). Each vulnerable sample is paired with its vendor-patched counterpart at the same source location, enabling patch-verified ground truth for binary firmware vulnerability detection research.

## Dataset Statistics
| Category | Count | % of positives |
|----------|-------|----------------|
| Memory Corruption | 52 | 34.7% |
| Memory Leak / Info Disclosure | 47 | 31.3% |
| SMM Callout | 21 | 14.0% |
| Stack Buffer Overflow | 20 | 13.3% |
| Out-of-bounds Read | 10 | 6.7% |
| **Total Positives** | **150** | **100%** |

| Source Family | Pairs | Count |
|---------------|-------|-------|
| BRLY | 116 | 232 |
| BRLY-LOGOFAIL | 24 | 48 |
| BRLY-DVA | 10 | 20 |
| **Total** | **150 pairs** | **300** |

## Directory Structure
The current public release stores all sample folders directly at the repository root; there is no top-level `finished/` directory.

```text
efi-vuln/
|-- README.md
|-- LICENSE
|-- CITATION.cff
|-- dataset_statistics.md
|-- sample_index.csv
|-- .gitignore
|-- BRLY-2021-003/
|   |-- meta_data.json
|   `-- src.c
|-- BRLY-2021-003-fixed/
|   |-- meta_data.json
|   `-- src.c
|-- ...
|-- BRLY-DVA-2023-003/
|   |-- meta_data.json
|   `-- src.c
|-- BRLY-DVA-2023-003-fixed/
|   |-- meta_data.json
|   `-- src.c
|-- ...
|-- BRLY-LOGOFAIL-2023-001/
|   |-- meta_data.json
|   `-- src.c
|-- BRLY-LOGOFAIL-2023-001-fixed/
|   |-- meta_data.json
|   `-- src.c
`-- ...
```

## Ground Truth Construction

### Patch-Verified Pairing
- **Positive samples (150)**: Vulnerable function-level snippets extracted from firmware versions predating the corresponding security fix. Their labels are stored in `meta_data.json` with `vulnerable: true` and a non-empty `vulnerability_type` list.
- **Negative samples (150)**: The same functions at the same code location in post-patch versions, stored as sibling directories named `<sample_id>-fixed`. Their metadata uses `vulnerable: false` and an empty `vulnerability_type` list.

### Rationale
This pairing controls for confounding factors such as function length, API usage, and surrounding code context that would otherwise let classifiers exploit superficial discriminators. The detection signal must therefore arise from vulnerability-relevant code differences between a vulnerable snippet and its matched patched counterpart.

## Vulnerability Categories
### Memory Corruption
Repo label: `Memory-Corruption-vulnerability`. This label covers memory safety flaws that corrupt program state, including corruption and related lifetime-management failures. CWE: TBD. Count: 52 positive samples.

### Memory Leak / Information Disclosure
Repo label: `Memory-contents-leak/information-disclosure-vulnerability`. These samples expose memory contents that should remain inaccessible, typically through missing bounds or disclosure checks. CWE: TBD. Count: 47 positive samples.

### SMM Callout
Repo label: `SMM-callout-vulnerability`. These samples involve privileged SMM handlers invoking functionality in a less trusted context, creating a control-flow or trust-boundary violation. CWE: TBD. Count: 21 positive samples.

### Stack Buffer Overflow
Repo label: `Stack-buffer-overflow-vulnerability`. These samples contain writes or copies that can exceed stack-allocated buffer bounds. CWE: TBD. Count: 20 positive samples.

### Out-of-bounds Read
Repo label: `Out-of-bounds-Read-vulnerability`. These samples read beyond valid object or buffer boundaries. CWE: TBD. Count: 10 positive samples.

## Sample Format
Each sample directory contains exactly two files:

### `meta_data.json`
- `vulnerability_type` (`list[str]`): Non-empty for vulnerable samples, empty list for patched counterparts.
- `vulnerable` (`bool`): `true` for pre-patch samples, `false` for post-patch samples.

Example:

```json
{
  "vulnerability_type": [
    "Stack-buffer-overflow-vulnerability"
  ],
  "vulnerable": true
}
```

### `src.c`
Function-level C source snippet, derived from decompilation output with manual cleanup.

A small number of samples (9/300) begin with `...`, indicating truncation. Users requiring complete function bodies should filter these samples before downstream analysis.

## Usage
### Load a single sample
```python
from pathlib import Path
import json

root = Path("efi-vuln")
sample_dir = root / "BRLY-2021-003"

meta = json.loads((sample_dir / "meta_data.json").read_text(encoding="utf-8"))
code = (sample_dir / "src.c").read_text(encoding="utf-8")

print(meta["vulnerable"])
print(meta["vulnerability_type"])
print(len(code))
```

### Count positive samples per vulnerability type
```python
from collections import Counter
from pathlib import Path
import json

root = Path("efi-vuln")
counter = Counter()

for meta_path in root.glob("*/meta_data.json"):
    meta = json.loads(meta_path.read_text(encoding="utf-8"))
    if meta["vulnerable"]:
        counter[meta["vulnerability_type"][0]] += 1

print(counter)
```

### Iterate over all patch-verified pairs
```python
from pathlib import Path
import csv

root = Path("efi-vuln")

with (root / "sample_index.csv").open(newline="", encoding="utf-8") as f:
    for row in csv.DictReader(f):
        sample_id = row["sample_id"]
        fixed_id = row["paired_fixed_id"]
        vuln_type = row["vulnerability_type"]
        vuln_code = (root / sample_id / "src.c").read_text(encoding="utf-8")
        fixed_code = (root / fixed_id / "src.c").read_text(encoding="utf-8")
        print(sample_id, fixed_id, vuln_type, len(vuln_code), len(fixed_code))
```

## Citation
```bibtex
@article{anonymous2026efivuln,
  title={efi-vuln: A Patch-Verified Dataset of UEFI Vulnerabilities},
  note={Under submission},
  year={2026}
}
```

## License
MIT

## Contact
Available upon de-anonymization after paper acceptance.
