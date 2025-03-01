
# Prerequisite Knowledge

[Command Prompt](../General/Command%20Prompt.md)

# Basic Commands

#### Creating/Cloning Repos
Create a new repo in the current directory:
```
git init
```

Grab an existing repo from a server:
```
git clone <url>
```

#### Changes
Check which files have been modified:
```
git status
```

#### Staging Files
You may have a lot of changes, but only want to commit some of them, to do this we "Stage" the files that are ready to be committed

Choose which files you want to commit (i.e. Staging files):
```
git add <individual file or folder>
```

Stage all modified files:
```
git add .
```

#### Committing Files
To commit the files that you staged in the previous step:
```
git commit -m "<message>"
```

To save a step, you can stage all changed files while you commit using:
```
git commit -am "<message>"
```

#### Sending your Files to the Server
```
git push
```

# Extra Links

https://www.jquery-az.com/git-commands/
https://dzone.com/articles/top-20-git-commands-with-examples
