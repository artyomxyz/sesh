# sesh
Shell

# COMPILATION. 
using `make` in sesh catalogue.

# LAUNCHING THE PROGRAMME.
`bin/sesh`

# WORK WITH GIT IN TERMINAL.
1) CREATE REPOSITORIES(Start a new repository or obtain one from an existing URL)
	$ git init [project-name]
	Creates a new local repository with the specified name
	$ git clone [url]
	Downloads a project and its entire version history

2) MAKE CHANGES(Review edits and craft a commit transaction)
	$ git status
	Lists all new or modified files to be committed
	$ git add [file]
	Snapshots the file in preparation for versioning
	$ git reset [file]
	Unstages the file, but preserve its contents
	$ git diff
	Shows file differences not yet staged
	$ git diff --staged
	Shows file differences between staging and the last file version
	$ git commit -m "[descriptive message]"
	Records file snapshots permanently in version history

3) GROUP CHANGES (Name a series of commits and combine completed efforts)
	$ git branch
	Lists all local branches in the current repository
	$ git branch [branch-name]
	Creates a new branch
	$ git checkout [branch-name]
	Switches to the specified branch and updates the working directory
	$ git merge [branch]
	Combines the specified branch’s history into the current branch
	$ git branch -d [branch-name]
	Deletes the specified branch

4)SYNCHRONIZE CHANGES
	Register a repository bookmark and exchange version history
	$ git fetch [bookmark]
	Downloads all history from the repository bookmark
	$ git merge [bookmark]/[branch]
	Combines bookmark’s branch into current local branch
	$ git push [alias] [branch]
	Uploads all local branch commits to GitHub
	$ git pull
	Downloads bookmark history and incorporates changes

5)SAVE FRAGMENTS
	Shelve and restore incomplete changes
	$ git stash
	Temporarily stores all modified tracked files
	$ git stash list
	Lists all stashed changesets
	$ git stash pop
	Restores the most recently stashed files
	$ git stash drop
	Discards the most recently stashed changeset