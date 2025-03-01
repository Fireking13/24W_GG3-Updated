
# What is Git?

Git is a Version Control System (VCS). VCSs allow you to store files along with their entire history of changes. Think Google Docs but with a lot more control for groups of files.

VCSs store the following info:
- The differences between all previous versions of the file
- Who made each change to the file
- When were the changes made
- more...

#### Popular Alternatives
- Perforce
- Subversion (SVN)
- many more...

#### Hosting Sites
Dedicated sites exist to store a copy of your repo, some cost money, some are free.
GitHub is the most popular, but keep in mind GitHub is not Git, it's just a server that can store a copy of your Git repo.

Others:
- GitLab
- Azure DevOps
- SourceForge
- many more...

# Installing

#### Core Git Software
Many Git clients, including Visual Studio have this installed for their own use, but if you want to use git from the command line, you need to install it yourself.
- Download here:
	- https://git-scm.com/
- Install
	- Default options are fine, this might require a reboot

#### Popular Client Software
These are all front-ends that use command line git behind the scenes and have better visualization tools for the status of files and more.
- Visual Studio has a git client built-in
	- Great for basic operations
- TortoiseGit (my favorite)
	- Great for more advanced operations
- GitHub Client

# Terminology

- **Repository/Repo**
	- The heart of version control, the repo stores all files and data related to changes made
- **Clone**
	- Make a copy of a repo from a server to your local file system
- **Remote server**
	- The server you clones your repo from
- **Commit**
	- When changes are made to files, those changes must get committed to the repo
	- Committing files only store them locally in your repo
- **Push**
	- Send any locally committed changes to a server (like GitHub)
- **Pull**
	- When working in teams or on multiple machines, if the server received changes you don't have, you need to "Pull" those changes from the server to your local repo

# General Process

- **Create a project** on your hosting site of choice (like Github)
- **Clone** that empty project to a local folder
- **Add some files** to your folder or **Modify existing files**
- **Commit** the new files or changes
- **Push** the changes to the server

# Ignoring Files

[Git Ignore](Git%20Ignore.md)

# Basic Command Line Commands

[Git Command Line Basics](Git%20Command%20Line%20Basics.md)
