# sesh
Shell

# COMPILATION. 

using `make` in sesh catalogue.

# LAUNCHING THE PROGRAMME.
`bin/sesh`

# WORK WITH GIT.
	"git clone git@github.com:artemsmirnov/sesh.git" - catalogue with written 
							out from github.com branch "master".
	"git submodule update --init" - use for recovery of holistic 
			project, cloning necessary submodules (additional branches).
	"git checkout -b branch_name" - creating of a new branch. Create while 
							in the branch 'master'.
	"git checkout branch_name" - jump to the existing github branch.
	"git pull origin master" - refresh master branch from github to the local repository.
	HOW TO MAKE A COMMIT:
	"git status" - list of all changed and added files. 
	"git add name_file.c" - preparing a commit adding the files to it.
	"git rm <file1> <file2>" - (or delete outdated files).
	"git commit -m "Commentary for a commit" " - performing a commit.
	"git push origin dev" - uploading the last version of dev branch to the remote server.



