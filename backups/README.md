# Repository Backups

Purpose
- Explain how and why periodic backups of this repo are created and how to restore them.

Why
- Recover from accidental deletion, destructive force-pushes, repo or account incidents, or remote outages.
- Keep immutable snapshots for releases or audits.

Create a dated bundle (offline snapshot)
- From repo root:
  - PowerShell: `git bundle create backups/dsa-YYYYMMDD_HHMMSS.bundle --all`

Restore from a bundle
- Clone from bundle:
  - `git clone path\to\backups\dsa-YYYYMMDD_HHMMSS.bundle DSA-from-bundle`
- Or in an existing folder:
  - `git clone /path/to/bundle --bare repo.git && git clone repo.git restored-working-copy`

Best practices
- Create bundles after releases or major changes; automate daily/weekly for active repos.
- Keep bundles offsite (cloud, external drive) and verify restores periodically.
- Do not track in git the bundle files in `backups/` only keep track of `backups/README.md`.