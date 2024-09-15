<h1 align="center">
    LANGUAGE: <img src="https://skillicons.dev/icons?i=git" alt="C Language Icon" width="30" height="30" />
</h1>


<div align="center"> 
 
 This document provides a quick reference to essential **GIT** functions:
 :-----:
 
</div>

<div align="center">
	<h2> A GOOD REPOSITORY HAS:</h2>
</div>

```python
							WHAT (is)
	
							HOW (to install it) 

							WHY (clone it)
```

## INDEX
1. [Account](#account)
2. [Repository](#repository)
3. [Commits](#commits)
4. [Branches](#branches)
5. [Submodules](#submodules-other-repository)


<hr>

## Account 

### Configure
```bash
git config --global user.name <user>
git config --global user.email <mail>
```

### Delete
```bash
git config --global --unset <user>
git config --global --unset <mail>
```

### User list
```bash
git config --list
```

<hr>





## Repository 
### Init
Create a repository in the current directory
```bash
git init
```

### Clone
```bash
git clone <URL>
```
### Status
Actual status of the repository (modified files, deleted, ...)
```bash
git status
```

### Pull
Update the local repository
```bash
git pull
```

<hr>




## Commits 

### Add and Push
```bash
git add .
git commit -m "<message>"
git push
```

### Rename the latest commit
```bash
git commit --amend -m "<new commit name>"
git push --force-with-lease
```

### Delete the latest commit
```bash
git reset --hard HEAD~1
git push --force
```

### Restore a deleted commit
```bash
git reflog
git reset --hard <id>
git push
```
By executing ```git reflog```, you will recieve a list of commits with this format: ```<id> <commit_message>```

<hr>



## Branches
### Print avaible branches
```bash
git branch
```
### Create
```bash
git branch <name>
```
### Move
```bash
git checkout <name>
```
### Create and move
```bash
git checkout -b <name>
```
### Merge
```bash
git merge <name>
```



<hr>

## Submodules (other repository) 

### Add
```bash
git submodule add https://github.com/<user>/<repo>.git path/to/submodule
git submodule update --init --recursive
git add .
git commit -m "Added submodule [name or path]"
git push origin main
```

### Update
```bash
git submodule update --remote
git add .
git commit -m "Updated submodule to latest version"
git push
```


<br>

<!--
ELIMINAR UN ARCHIVO
> git rm nombre_archivo
> git rm -r nombre_archivo



MIRAR LAS BRANCHS Y LA ACTUAL EN VERDE
> git branch

CREAR UNA BRANCH
> git branch nombre_branch

CAMBIAR UNA BRANCH
> git checkout nombre_branch

PUSHEAR LA BRANCH
> git push origin outdated

ELIMINAR UNA BRANCH
> git branch -D nombre_branch
-->
