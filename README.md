# ALPC-Block-POC
Blocking Windows EDR agents by registering an own IPC object in the Object Manager’s namespace (CVE-2023-3280, CVE-2024-5909, CVE-2024-20671 and others without assigned CVEs)

# Introduction
This repository contains example code demonstrating how to exploit DoS vulnerabilities present in most tested Windows EDR agents. This can be achieved by a low-privileged user.

The corresponding blog post detailing the vulnerability can be found here: [IG-Labs Blog](https://labs.infoguard.ch/posts/edr_part3_one_bug_to_stop_them_all/)

# Background
Most Windows EDR agents rely on Inter-Process Communication (IPC) between their various components. If an attacker registers a specific object (e.g., \RPC Control\Palo-Alto-Networks-Traps-DB-Rpc for Cortex) before the EDR agent initializes, the EDR's user-mode components will crash upon startup. This renders the EDR completely inactive.

A system reboot is required for this exploit to be effective. It's also potentially exploitable during EDR updates.

# Usage
The provided example code demonstrates the vulnerability [CVE-2023-3280](https://security.paloaltonetworks.com/CVE-2023-3280).

### Steps:
 - Compile the project
 - Register the compiled binary to run automatically during early startup. For example:
   - A scheduled task with the highest possible priority (Priority=2 for low-privilege users and Priority=0 for local administrators).
   -  A trigger set to user logon.
 - Reboot the system using a method that leverages Automatic Restart Sign-On ([ARSO](https://learn.microsoft.com/en-us/windows-server/identity/ad-ds/manage/component-updates/winlogon-automatic-restart-sign-on--arso-)), such as clicking "Reboot" in the GUI. This ensures that user startup tasks execute early in the boot process without waiting for a manual user login.

# Notes
Instead of ALPC ports, Named Pipes can also be used to achieve the same result. It's likely there are other unpatched vulnerabilities of this nature, as we haven't been able to test all EDR vendors.
