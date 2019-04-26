# Instruction for contributors:registered:

## Clone the project (:heavy_exclamation_mark:just first time)
```bash
git clone https://github.com/tumasyan/CMS_VBF_Hbb_2017_18.git
```
## Update branch list (local :arrow_left: remote)
```bash
git remote update origin --prune
```
## See current branch and available list of branches
```bash
git branch -a
```
## Change the branch (IF NEEDED)
```bash
git checkout branch_name
```
## Update local branch (local :arrow_left: remote)
```bash
git pull
```
## Add new files/directories
```bash
git add . 
```
or
```bash
git add --all .
```
## Commit your changes
```bash
git commit -m "description of your change"
```
## Update remote branch (local :arrow_right: remote)
```bash
git push
```
> # Less used commands
> ### Delete local branch (from your pc)
> git branch -D branch_name
> ### Delete remote branch (from github.com)
> git push origin --delete branch_name
> ### Create new local branch
> git checkout -b new_branch_name
> ### Send this :arrow_up: new local branch to remote  (local :arrow_right: remote) (:heavy_exclamation_mark:just first time, then just ```bash git push ```)
> git push -u origin new 
