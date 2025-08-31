from pathlib import Path;
import multiprocessing;
import re;
import os;


def MyFilePath():
    """获得自身所在路径"""
    # 获取当前自身所在路径
    file_path = Path(__file__).resolve();
    # 统一路径分隔符`/`
    build_path = (file_path.parent / "build/").as_posix();

    return build_path;

def vcpkg_cmake_path():
    """查找vcpkg.cmake路径"""
    # 尝试获取VCPKG_ROOT环境变量
    vcpkg_path = os.environ.get('VCPKG_ROOT');

    if not vcpkg_path:
        # 如果VCPKG_ROOT环境变量不存在，尝试在PATH中查找
        import shutil
        vcpkg_exe = shutil.which('vcpkg.exe') or shutil.which('vcpkg');
        if vcpkg_exe:
            # 获取vcpkg.exe所在目录
            vcpkg_path = os.path.dirname(vcpkg_exe);

    if vcpkg_path:
        vcpkg_cmake_path = os.path.join( \
            vcpkg_path, \
            'scripts', \
            'buildsystems', \
            'vcpkg.cmake'
        );

        # 统一路径分隔符为正斜杠
        return vcpkg_cmake_path.replace('\\', '/');
    else:
        # 如果失败则尝试默认路径
        return "C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake";

def target_exeName():
    """从CMakeLists.txt中提取add_executable的目标名"""
    cmakelists_path = \
    Path(__file__).resolve().parent / "CMakeLists.txt";

    with open(cmakelists_path, "r", encoding="utf-8") as f:
        content = f.read();

    # 移除所有注释 (`#`开头到行尾的内容)
    content_no_comments = re.sub(r'#.*$', '', content, flags=re.MULTILINE)

    # 移除多余的空白字符和换行符，保留单个空格
    content_clean = re.sub(r'\s+', ' ', content_no_comments);

    # 匹配 add_executable(target_name ...);
    match = re.search( \
        r'add_executable\s*\(\s*([^\s\)]+)', \
        content_clean, \
        re.IGNORECASE
    );

    if not match:
        raise RuntimeError(
            "\33[91m未在CMakeLists.txt中找到add_executable。\33[0m"
        );

    target_name = match.group(1).strip();
    return target_name;

def loginfi(string):
    """打印日志信息"""
    print(f"\33[4;38;2;165;224;117mbuild.py\33[0m：{{ \33[4;97m{string}\33[0m }}");

def Build():
    """执行构建任务"""
    loginfi("开始执行构建命令");

    """
    1、指定CMakeLists.txt路径与生成器为ninja。
    2、导出编译命令提供给clangd使用。
    3、指定C编译器为clang。
    4、指定CXX编译器为clang++。
    5、指定vcpkg.cmake文件路径。
    """
    string = \
        f"cmake .. -G \"Ninja\" " \
        f"-DCMAKE_EXPORT_COMPILE_COMMANDS=ON " \
        f"-DCMAKE_C_COMPILER=clang " \
        f"-DCMAKE_CXX_COMPILER=clang++ " \
        f"-DCMAKE_TOOLCHAIN_FILE={vcpkg_cmake_path()}";

    results = os.system(f"{string}");
    if results != 0:
        loginfi("\33[4;91m构建命令执行失败");
        return;

def Compile():
    """执行编译任务"""
    loginfi("开始执行编译命令");
    try:
        # 获取CPU最大线程数并执行对应编译命令
        cpu_count = multiprocessing.cpu_count();
        results = os.system(f"ninja -j{cpu_count}");
    except NotImplementedError:
        # 如果获取CPU线程数失败则使用默认命令
        results = os.system("ninja");

    if results != 0:
        loginfi("\33[4;91m编译命令执行失败");
        return;

    loginfi("尝试执行程序");
    results = os.system(f"{target_exeName()}");


if __name__ == "__main__":
    os.chdir(MyFilePath());
    loginfi("已进入构建目录");

    """按需选择构建或编译运行"""
    Build();
    Compile();