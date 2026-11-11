# Data-flow path fixtures

Small C fixtures for measuring how many source-to-sink paths a data-flow engine reports. `src/fx.c` lists each case
and its expected verdict. The workflow runs two path queries on it (`queries/`) and keeps the raw results and SARIF as
a run artifact.
