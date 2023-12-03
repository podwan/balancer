# github单人项目使用方式

借用github服务器，实现项目远程存储，多地编辑

1.  在github里面创建代码仓库repository并获取url
2. 首次在本地编辑项目执行：git clone "repository url"， 非首次的话执行 git pull origin main, 获取远程最新文件
3. 编辑源文件后 git add, git commit, git push origin main，将本地编辑的文件更新到github

# github多人项目使用方式

借用github服务器，实现项目远程统一管理，多人协作

1.  在github里面创建代码仓库repository并获取url
2. 首次在本地编辑项目执行：git clone "repository url"， 非首次的话执行 git pull origin main, 获取远程最新文件
3. 创建分支：git checkout  -b my-feature, 编辑源文件后 git add, git commit, git push origin my-feature
4. 如果发现github源文件在push my-feature之前已被更新的话（这是可能要在更新过的main上进行my-feature的测试），则先将本地分支先切换到main分支：git checkout main, 将本地文件切换回到第2步的状态
5. 执行git pull origin main，将main分支进行更新，然后git checkout my-feature切换到my-feature 分支，执行git rebase main将更新过的main添加进my-feature
6. 测试ok的话git push -f origin my-feature(-f force push)，最终在github页面上形成一个pull request, 项目main发起人经过审查后就可以merge
7. 切换git checkout main, 删除git branch -D my-feature, git pull origin main将本地从github进行更新 