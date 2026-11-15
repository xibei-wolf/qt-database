# Qt 数据库

Qt 数据库访问练习（QSqlDatabase / QSqlQuery）。

## 包含的工程

| 目录 | 说明 |
|---|---|
| `sqldemo` | 数据库访问 |

## 构建

每个子目录是独立的 qmake 工程：

```bash
cd sqldemo
# 需要 Qt 环境（示例为 Qt 6.8.3 MinGW 64-bit）
qmake && mingw32-make
# 或用 Qt Creator 直接打开 .pro 文件
```

> 若缺少 `build/` 目录下的桌面套件路径，用 qmake 重新生成即可：
> `qmake && qmake -o Makefile && mingw32-make`

## 说明

- 构建产物（`build/`、moc/uic 生成文件、目标文件）已通过 `.gitignore` 排除
- 原始源码完整保留，未做任何修改
