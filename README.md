本测试集用于测试vast-front将C++翻译为IR的功能是否正确，由clang项目中的`test/CodeGenCXX`测试集移植而来

### 快速开始

1. 本测试集使用llvm lit运行测试，请确保已安装了lit
2. 根据`config.example`创建配置文件`config`，并填入本机环境。一些重要配置项如下：
    - `TESTCASE`：指定`testcases/`下的一个测试用例子集运行测试。
    该变量为一个分号隔开的目录或文件的列表（`"test1[;test2[;test3...]]"`），每一项均为相对于`testcases/`的相对路径。
    为`"."`或为`""`时测试所有测试用例
    - `PARALLEL`：并行进程数，每个编译单元使用一个vast-front进程编译。启用`TEST_DB`测试数据库时速度较慢，建议使用16或32进程性能最佳
    - `CLEAN_DB`：使每个进程在将本编译单元dump到数据库前先清空数据库。因此不能和`PARALLEL > 1`结合使用
3. 运行自动化测试脚本`test.sh`（注意：必须在测试集根目录下运行），该脚本：
   1. 读取`config`中的配置
   2. 拉取最新提交。目前测试用例的分类尚未完成，可能随时更新
   3. 配置并运行测试
   4. 运行脚本统计测试结果
4. 查看测试结果
   - `build/Testing/Temporary/LastTest.log`显示具体测试结果（报错信息、测试时间等）
   - `build/process.log`显示实时测试进度，数据库测试在16进程下大约需要5~6分钟

#### 注意事项
- 一个编译单元可能会按照不同参数被编译多次，因此在`build/process.log`中观察到重复的文件是正常的
- verifyDB pass在dump到数据库前会删除同名的module节点，保证parse入口唯一，因此在每次测试前不清理数据库不会导致错误。\
  但verifyDB pass只会删除module节点，不会递归删除，因此为避免数据库过大，在每次运行测试前，建议手动清空数据库：
  `MATCH (n) DETACH DELETE n;`

### 测试集结构

- `testcases/`
  - `*.cpp, *.cppm`：测试用例，每个测试用例都是一个单文件
  - `Inputs/, typeinfo`：测试用例的依赖
  - `ignore/`：忽略的测试用例
- `lit.cfg.py, lit.site.cfg.py.in`：lit的配置文件

### 测试集配置

本测试集使用llvm lit运行测试

#### 更改测试用例的目录结构

本测试集删减了clang的CodeGenCXX测试集，粗略去除了一些对vast不关心的内容的测试，比如目标平台相关的语法扩展和IR信息、IR中的调试信息等，目前共有721个测试用例。这些测试用例并未归类，你可以在实现vast对C++某个语法的翻译的同时筛选出相应测试用例并将其归入相应子目录（比如将有关构造函数的测试用例归入`testcases/constructor/`目录），这样也有助于划分我们各自负责的测试用例。同时这些测试用例中仍然包含一些我们不关心的测试用例，发现这些测试用例后你可以将其归入`testcases/ignore/`目录。如果想知道某个测试用例的原本目的，可以参考clang项目中的同名测试用例，查看其原本的编译和测试命令。**更改目录结构后请及时更新仓库。**

`lit.cfg.py`中可以在`config.excludes`中指定忽略的测试目录

#### 更改编译命令

lit按照测试用例中的注释`// RUN: <command>`指定的命令运行测试，为了更灵活地配置测试命令，其中可以包括可被替换为相应文本的替换符。lit有一些内置替换符，可参考[llvm lit](https://llvm.org/docs/CommandGuide/lit.html#substitutions)，也可以通过`lit.cfg.py`中的`config.substitutions.append()`自定义替换规则。其中`%driver`指定编译工具、`%target`指定生成目标、`%output-suffix`指定生成文件的后缀，**你需要将这些替换符指定为vast相关的命令行参数**。

#### 更改测试命令

若测试用例中的每条测试命令都成功执行，则测试成功。本测试集除测试编译是否成功外，还使用llvm FileCheck检查编译出的内容是否符合要求。FileCheck使用模板文件中的注释`// CHECK: <pattern>`、`// CHECK-NOT: <pattern>`等指定的匹配模式匹配被检查的文件。通常将这些注释写在测试用例中，但为了使用替换符灵活指定匹配模式，本测试集使用一个临时文件指定测试注释（参考测试命令`%filecheck`的定义）。`%check`指定了匹配模式，目前对每个生成文件的检测都是相同的，仅保证其中不含`unsup.`和`unreach.`操作。如有补充，你可以修改`%filecheck`和`%check`。
