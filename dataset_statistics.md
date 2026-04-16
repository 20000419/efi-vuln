# Dataset Statistics

## Summary
This file reports statistics computed directly from the current public repository state.

- Total sample directories: `300`
- Vulnerable samples: `150`
- Patched samples: `150`
- Patch-verified pairs: `150`
- Binary files: `0`
- Structural consistency: every sample directory contains exactly `meta_data.json` and `src.c`

Category labels are taken from `meta_data.json` for vulnerable samples only. Patched counterparts store `vulnerability_type: []`, so per-category patched counts are implicit through the one-to-one pairing rule. Source family labels are inferred from directory prefixes: `BRLY-*`, `BRLY-DVA-*`, and `BRLY-LOGOFAIL-*`.

## Category Distribution
| Category | Count | % of positives |
|----------|-------|----------------|
| Memory Corruption | 52 | 34.7% |
| Memory Leak / Info Disclosure | 47 | 31.3% |
| SMM Callout | 21 | 14.0% |
| Stack Buffer Overflow | 20 | 13.3% |
| Out-of-bounds Read | 10 | 6.7% |
| **Total Positives** | **150** | **100%** |

## Positive / Negative Split
| Split | Count | % of total |
|-------|-------|------------|
| Vulnerable | 150 | 50.0% |
| Patched | 150 | 50.0% |
| **Total** | **300** | **100.0%** |

## Source Family Distribution
| Source Family | Pairs | Count |
|---------------|-------|-------|
| BRLY | 116 | 232 |
| BRLY-LOGOFAIL | 24 | 48 |
| BRLY-DVA | 10 | 20 |
| **Total** | **150 pairs** | **300** |

## File and Snippet Size Distribution
No binary artifacts are present in the repository. The dataset currently consists only of `src.c` snippets and `meta_data.json` files.

| Artifact | Count | Min bytes | Max bytes | Mean bytes |
|----------|-------|-----------|-----------|------------|
| `src.c` | 300 | 210 | 16122 | 2744.73 |
| `meta_data.json` | 300 | 57 | 130 | 84.49 |

| `src.c` line metric | Value |
|---------------------|-------|
| Min lines | 8 |
| Max lines | 594 |
| Mean lines | 94.23 |
| Median lines | 74.5 |

## Observed Anomalies
- `9 / 300` `src.c` files begin with `...`, indicating truncated snippets rather than fully preserved function bodies.
- `2 / 300` `src.c` files contain fewer than 10 lines.
- No malformed metadata files were observed during scanning.

## Reproducibility Notes
- Pairing is verified by naming: every vulnerable sample `<sample_id>` has a matching patched sample `<sample_id>-fixed`.
- The repository currently does not expose CVE IDs, advisory URLs, firmware version strings, or explicit function-name metadata in machine-readable form.
- `sample_index.csv` provides a derived index of all vulnerable samples and their paired patched counterparts using only repository-local information.
