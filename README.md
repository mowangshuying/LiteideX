<!-- Welcome to LiteIDE X -->

LiteIDE X
=========

![liteide-logo](liteidex/liteide-logo/liteide.png)

### Introduction

_LiteIDE is a simple, open source, cross-platform Go IDE._

* Version: X38.6
* Author: [mowangshuying](https://github.com/mowangshuying)

### Features

* Core features
    * System environment management
    * MIME type management 
    * Configurable build commands
    * Support files search replace and revert
    * Quick open file, symbol and commands
    * Plug-in system
    * Integrated terminal

* Advanced code editor
    * Code editor supports Golang, Markdown and Golang Present
    * Rapid code navigation tools
    * Syntax highlighting and color scheme
    * Code completion
    * Code folding
    * Display save revision
    * Reload file by internal diff way

* Golang support
    * Support Go1.18~Go1.21 generics
    * Support Go1.18 go.work
    * Support Go1.11 Go modules
    * Support Go1.5 Go vendor
    * Support Go1 GOPATH
    * Golang build environment management
    * Compile and test using standard Golang tools
    * Custom GOPATH support system, IDE and project
    * Custom project build configuration
    * Golang package browser
    * Golang class view and outline
    * Golang doc search and api index
    * Source code navigation and information tips
    * Source code find usages
    * Source code refactoring and revert
    * Integrated  [gocode](https://github.com/visualfc/gocode) clone of [nsf/gocode](https://github.com/nsf/gocode)
    * Integrated [gomodifytags](https://github.com/fatih/gomodifytags)
    * Support source query tools guru
    * Debug with GDB and [Delve](https://github.com/derekparker/delve)

### Supported Systems
* Windows x86 (32-bit or 64-bit)

### LiteIDE Command Line
	liteide [files|folder] [--select-env id] [--local-setting] [--user-setting] [--reset-setting]
	
	--select-env [system|win32|cross-linux64|...]     select init environment id
	--local-setting   force use local setting
	--user-setting    force use user setting
	--reset-setting   reset current setting ( clear setting file)	

### Update liteide tools for support new Golang Version	

	go install github.com/visualfc/gotools@latest
	go install github.com/visualfc/gocode@latest
	
	Windows/Linux: copy GOPATH/bin gotools and gocode to liteide/bin
	MacOS: copy GOPATH/bin gotools and gocode to LiteIDE.app/Contents/MacOS

### Documents
* How to Install
<https://github.com/visualfc/liteide/blob/master/liteidex/deploy/welcome/en/install.md>
* FAQ
<https://github.com/visualfc/liteide/blob/master/liteidex/deploy/welcome/en/guide.md>
* 安装 LiteIDE
<https://github.com/visualfc/liteide/blob/master/liteidex/deploy/welcome/zh_CN/install.md>
* FAQ 中文
<https://github.com/visualfc/liteide/blob/master/liteidex/deploy/welcome/zh_CN/guide.md>

### Links
* LiteIDE Source code
<https://github.com/visualfc/liteide>
* Gotools Source code
<https://github.com/visualfc/gotools>
* Gocode Source code
<https://github.com/visualfc/gocode>
* Changes
<https://github.com/visualfc/liteide/blob/master/liteidex/deploy/welcome/en/changes.md>


### Donate
* https://visualfc.github.io/support
