class Dependencies:
    def __init__(self):
        
        self.is_exe = True
        self.files = ['main.py', 'git.py', 'additional.py']
        
        self.path_to = {}
        if (self.is_exe): self.path_to['root'] = '../'
        else: self.path_to['root'] = ''

        self.data = {
            'name_project' : {
                'old' : None,
                'new' : None
            },
            'directory' : None 
        }


    def has_dependencies():
        return True

