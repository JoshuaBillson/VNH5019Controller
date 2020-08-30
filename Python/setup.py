from setuptools import setup

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    install_requires=["pyserial==3.4", "smbus2==0.3.0"],
    name="VNH5019_Serial_Controller",
    version="0.0.2",
    author="Joshua Billson",
    author_email="jmbillson@outlook.com",
    description="A library for controlling a Pololu VNH5019 Motor Controller Shield via USB Serial and I2C.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/JoshuaBillson/VNH5019Controller",
    packages=["VNH5019Controller"],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.5",
)
