# Instruction for contributors

## Clone project (just first time)
```bash
git clone https://github.com/tumasyan/CMS_VBF_Hbb_2017_18.git
```
## Update branch list from remote to local
```bash
git remote update origin --prune
```
## See current branch and available list of branches
```bash
git branch -a
```
## Change the branch. (IF NEEDED)
```bash
git checkout branch_name
```
## Update your local branch
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
## You commit your changes
```bash
git commit -m "description of your change"
```
## Update remote project
```bash
git push
```
> # Less used commands
> ### Delete local branch (from your pc)
```bash
git branch -D branch_name
```
> ### Delete remote branch (from github.com)
```bash
git push origin --delete branch_name
```
> ### Create new local branch
```bash
git checkout -b new_branch_name
```
> ### Send this new local branch to remote
```bash
git push -u origin new (just first time)
```
