import subprocess
import os
import sys

def check_command(command):
    return subprocess.call(f"command -v {command}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0

def install_packages(packages):
    for pkg in packages:
        if not check_command(pkg):
            if check_command("pkg"):
                subprocess.run(["pkg", "install", pkg, "-y"], check=True)
            elif check_command("apt"):
                subprocess.run(["sudo", "apt", "install", pkg, "-y"], check=True)
            elif check_command("apt-get"):
                subprocess.run(["sudo", "apt-get", "install", pkg, "-y"], check=True)
            elif check_command("pacman"):
                subprocess.run(["sudo", "pacman", "-S", pkg, "--noconfirm"], check=True)
            elif check_command("dnf"):
                subprocess.run(["sudo", "dnf", "-y", "install", pkg], check=True)
            elif check_command("yum"):
                subprocess.run(["sudo", "yum", "-y", "install", pkg], check=True)
            else:
                print("Unsupported system, cannot install packages.")
                sys.exit(1)

def install_pip_package(package):
    if not check_command("pip"):
        print("pip is not installed. Please install pip first.")
        sys.exit(1)
    subprocess.run(["pip", "install", package], check=True)

def compile_cpp():
    subprocess.run(["g++", "-o", "bin/nightstalker", "bin/nightstalker.cpp"], check=True)

def main():
    required_commands = ["clang", "curl", "tor"]
    if not all(check_command(cmd) for cmd in required_commands):
        packages = ["php", "curl", "unzip"]
        install_packages(packages)

    if not check_command("tor"):
        install_packages(["tor"])

    install_pip_package("torspy")

    compile_cpp()

    if os.path.exists("/data/data/com.termux/files/usr/bin"):
        destination = "/data/data/com.termux/files/usr/bin/nightstalker"
    elif os.path.exists("/usr/bin"):
        destination = "/usr/bin/nightstalker"
    else:
        print("Unsupported system.")
        sys.exit(1)

    subprocess.run(["mv", "bin/nightstalker", destination])
    subprocess.run(["chmod", "+x", destination])

if __name__ == "__main__":
    main()
