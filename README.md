# Instruction for contributors

## Clone project (just first time)
git clone https://github.com/tumasyan/CMS_VBF_Hbb_2017_18.git

## Update branch list from remote to local
git remote update origin --prune

## See current branch and available list of branches
git branch -a

## Change the branch. (IF NEEDED)
git checkout branch_name

## Update your local branch
git pull

## Add new files/directories
git add . 
    or
git add --all .

## You commit your changes
git commit -m "description of your change"

## Update remote project
git push





# Less used commands
### Delete local branch (from your pc)
> git branch -D branch_name

### Delete remote branch (from github.com)
> git push origin --delete branch_name

### Create new local branch
> git checkout -b new_branch_name

### Send this new local branch to remote
> git push -u origin new (just first time)

