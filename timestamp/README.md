# Timestamp BOF
## Summary
Brute Ratel BOF that modifies the Creation, Last Access, and Last Write timestamps of a file on disk. This is useful for timestomping dropped payloads to match legitimate surrounding files.
Timestamp in `"YYYY-MM-DD HH:MM:SS"` format (UTC)


## Usage
```bash
coffexec out64/timestamp64.o C:\Users\admin\Downloads\payload.exe "2021-09-02 16:05:01"
```
