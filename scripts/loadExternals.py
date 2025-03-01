import os
import subprocess

# Define file and target directory
externals_file = "scripts/externals.txt"
dependencies_dir = "dependencies"

# Ensure the dependencies directory exists
os.makedirs(dependencies_dir, exist_ok=True)

# Read the externals file line by line
if not os.path.exists(externals_file):
    print(f"Error: {externals_file} not found!")
    exit(1)

with open(externals_file, "r") as file:
    repos = [line.strip() for line in file if line.strip()]

for repo in repos:
    # Convert HTTPS to SSH if needed
    if repo.startswith("https://github.com/"):
        ssh_repo = repo.replace("https://github.com/", "git@github.com:")
    else:
        ssh_repo = repo  # Assume it's already in SSH format

    repo_name = repo.rstrip(".git").split("/")[-1]  # Extract repository name
    target_path = os.path.join(dependencies_dir, repo_name)

    if os.path.exists(target_path):
        print(f"Skipping {repo_name}, already exists.")
        continue

    # Try cloning using SSH, fallback to HTTPS if SSH fails
    try:
        print(f"Cloning {ssh_repo} into {dependencies_dir}...")
        subprocess.run(["git", "clone", ssh_repo, target_path], check=True)
    except subprocess.CalledProcessError:
        print(f"SSH failed, trying HTTPS for {repo_name}...")
        subprocess.run(["git", "clone", repo, target_path], check=True)

print("All repositories have been processed.")
