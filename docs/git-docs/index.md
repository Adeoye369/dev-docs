# Git Documentation

## Branching 

```bash
git branch dev_codes # Creating a new branch "dev_codes"
git checkout dev_codes # Switch to the new branch "dev_codes"

git checkout -b dev_codes2 # Create & switch to new branch "dev_codes2"

```

Use `git branch -d <branch_name>` to delete a merged branch.
USe `git branch -D <branch_name>` to force delete an unmerged branch

## Remote Information

```bash
# To obtain only the remote URL:
git config --get remote.origin.url

# If you require full on a network of remote repo where the origin resides:
git remote show origin

# This will print all your remotes' fetch/push URLs:
git remote -v   
```

## fetch, merge and pull

```bash
# use `git fetch origin <remote-branch-name>`  fetching from the remote branch without merge
git fetch origin L8-start # fetch from L8-start branch

#After fetching, you need to merge the changes from the remote-tracking branch
#into your current local branch.
git merge origin/L8-start
git merge --abort # to abort merge
```

## Undo a Git merge COMMIT that hasn't been pushed yet

if you accidentally merge a branch or you just want to under branch that has been **merged and commited
**

```bash
git reset --hard <commit_sha>

git reset --hard HEAD~1 # There's also another way:
```