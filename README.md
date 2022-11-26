# FastCrypt

FastCrypt is a very simple encryption and decryption program. It generates random string, converts it to int and uses it as encryption key. Then saves encrypted file with key as extension. Decrypting is straight forward, just choose encrypted file and it will return original.

### For example

- input:      file.txt
- string key: sny
- int key:    110123106
- output:     file.sny

## Compilation

```bash
cmake .
```
```bash
make
```
```bash
./crypt <arguments>
```
## Usage

Use
```bash
./crypt encrypt <filepath>
```
to encrypt file.

OR

Use
```bash
./crypt decrypt <filepath>
```
to decrypt file.

## License

[MIT](https://choosealicense.com/licenses/mit/)
