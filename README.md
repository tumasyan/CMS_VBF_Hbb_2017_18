# Instruction for contributors

## Clone project (just first time)
git clone https://github.com/tumasyan/CMS_VBF_Hbb_2017_18.git

## Update branch list from remote to local
git remote update origin --prune

## See available list of branches
git branch -a

## Go to development version
git checkout dev (for example)

## Update branch from remote
git pull

## Add new files/directories
git add --all .

## You comments to changes
git commit -m "description"

## Update remote project
git push


# Less used commands
## Delete local branch (from your pc)
git branch -D branch_name

## Delete remote branch (from github.com)
git push origin --delete branch_name
