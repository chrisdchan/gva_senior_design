## Enviornment Setup

1. Clone repository locally. In a terminal navigate to the project directory and run:
```
git clone https://github.com/chrisdchan/gva_senior_design.git 
```

2. Next run this to create virtual env
```
conda env create -f environment.yml
```

3. Activate the virtual env
```
conda activate gva
```

4. You should be able to run
```
python hello.py
```

## Other
Command to update enviornment.yml if new dependencies are added
```
conda env export > environment.yml
```
