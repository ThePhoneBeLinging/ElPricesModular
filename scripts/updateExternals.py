import os
import subprocess

# Define the dependencies directory
dependencies_dir = "dependencies"

# Ensure the directory exists
if not os.path.exists(dependencies_dir):
    print(f"Error: {dependencies_dir} does not exist!")
    exit(1)

# List all folders in dependencies directory
repos = [d for d in os.listdir(dependencies_dir) if os.path.isdir(os.path.join(dependencies_dir, d))]

if not repos:
    print("No repositories found in dependencies directory.")
    exit(0)

for repo in repos:
    repo_path = os.path.join(dependencies_dir, repo)
    print(f"Pulling latest changes in {repo}...")
    try:
        subprocess.run(["git", "-C", repo_path, "pull"], check=True)
    except subprocess.CalledProcessError:
        print(f"Failed to pull {repo}, please check manually.")

print("All repositories have been processed.")