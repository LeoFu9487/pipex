# pipex

usage : 

```./pipex file1 cmd1 cmd2 file2```
works as 
```<file1 cmd1 | cmd2 >file2 ```

bonus ( >> and << are optional) : 
```./pipex_bonus '<<' eof_message cmd1 cmd2 cmd3 ... cmdn file2 '>>'```
works as 
```<< eof_message cmd1 | cmd2 | cmd3 | ... | cmdn >> file2```
