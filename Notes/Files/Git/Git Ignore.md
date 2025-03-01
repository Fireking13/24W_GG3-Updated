
# Basics

In the root of your git repo, create a file called "**.gitignore**".

Since this file starts with a ".", Windows will hide it by default, so check your Windows Explorer options and view hidden files.

In this file, you can specific files or folders to ignore.

Ignoring a file will make the file not appear when checking the status of your repo. If the file was previously committed it will continue to show up and changes will be committed.

If you committed a file you meant to ignore, you need to remove it from the repo to avoid it being constantly committed. Keep in mind, it still exists in the history, so if the file was large, cloning the repo will still take time and space for that file.

# Examples

Ignore a file with an exact name in any folder:
```
debug.txt
```

Ignore a file with an exact name in the root folder:
```
/debug.txt
```

Ignore all files with a specific extension in any folder:
```
*.pdb
```

Ignore all folders with an exact name, this will also ignore a file with the same name and no extension:
```
build
```

Ignore a specific file or folder buried in another folder
```
build/intermediate
build/project.pdb
```

# Multiple ignore files

You can put **.gitignore** files in folders deeper than the root, they will consider a slash at the front of an entry to be the folder they are in.
