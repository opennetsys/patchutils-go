# go-patchutils

> Go bindings for [https://github.com/twaugh/patchutils](patchutils)

Currently only supports `combinediff`

```go
out, err := patchutils.Combine("file1.patch", "file2.patch")
if err != nil {
  t.Fatal(err)
}
```

## Test

```bash
make test
```

## License

MIT
