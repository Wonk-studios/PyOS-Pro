import os

log("PyOS 0.0.D")

def log(message):
    print(message)

def check_c_module():
    return os.path.exists("/tmp/report.txt")

class PS:
    @staticmethod
    def kernel(cmd):
        try:
            if not check_c_module():
                raise ValueError("C module report file is not present")
        except ValueError as e:
            log(f"Error: {e}")
        
        if cmd == "shutdown":
            shutdown_kernel()
        elif cmd == "restart":
            restart_kernel()
        elif cmd == "sleep":
            sleep_kernel()
        elif cmd == "hibernate":
            hibernate_kernel()
        else:
            log(f"Unknown command: {cmd}")

def shutdown_kernel():
    log("Shutting down...")

def restart_kernel():
    log("Restarting...")

def sleep_kernel():
    log("Sleeping...")

def hibernate_kernel():
    log("Hibernating...")

# Example usage
PS.kernel("shutdown")