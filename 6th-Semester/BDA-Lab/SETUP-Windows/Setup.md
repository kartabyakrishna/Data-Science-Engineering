# Setting up prerequisites - wsl & Docker 

## Step 1: Install Windows Subsystem for Linux (WSL)

Open any terminal (cmd or PowerShell) as an administrator and run the following command:

```bash
wsl --install
```

Follow the prompted steps to set up WSL, including providing a username and password. Once completed, close and reopen the shell.

## Step 2: Install Docker

Open the terminal in WSL and execute the following commands to set up Docker using the apt repository:

```bash
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

sudo apt-get update
```

Note: If you use an Ubuntu derivative distro, such as Linux Mint, you may need to use UBUNTU_CODENAME instead of VERSION_CODENAME.

## Step 3: Install Docker Packages

To install the latest version of Docker, run the following command:

```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

## Step 4: Verify Docker Installation

Ensure that Docker Engine is installed successfully by running the following command:

```bash
sudo docker run hello-world
```

This command downloads a test image and runs it in a container. When the container runs, it prints a confirmation message and exits.

# Hadoop Installation

## Step 1: Clone docker-hadoop repository

Clone the docker-hadoop repository from GitHub. If you're using the console, run the following command:

```bash
git clone https://github.com/big-data-europe/docker-hadoop
```

After executing this command, you should have the following folder structure:

![Folder structure after cloning the GitHub repository](link-to-image)

## Step 2: Start necessary containers using docker-compose

Run the following command to start the necessary containers. This command will initiate the five required containers. If it's the first time, you may need to wait for the download to finish.

```bash
docker-compose up -d
```

Docker Compose allows running multi-container Docker applications using a YAML file, executing all defined commands. Check if all five containers are running by typing:

```bash
docker ps
```

Ensure that the containers are up and running.

![Starting all the necessary containers](link-to-image)

## Step 3: Access the master node "namenode"

Get into the namenode container, which serves as the master node of the Hadoop cluster. It's a mini-linux environment that allows managing the HDFS file system.

```bash
docker exec -it namenode bash
```

![Getting into the namenode container](link-to-image)

## Step 4: Create folder structure to allocate input files

List all files in the HDFS system:

```bash
hdfs dfs -l /
```

Create the required folder structure (/user/root/) as Hadoop works with this defined structure:

```bash
hdfs dfs -mkdir -p /user/root
```

Verify if the folder was created successfully:

```bash
hdfs dfs -ls /user/
```

![Creating our /user/root folder](link-to-image)

Continue to the next step when you're ready.
