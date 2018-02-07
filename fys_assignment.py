from subprocess import call # to launch the assignment program
from os import remove       # for cleaning up
import os.path 				# for checking the file extension
import pandas
import numpy as np

try:
	# python3
	from tkinter import Tk, Label, Button, BOTH, Frame, BooleanVar, Checkbutton
	from tkinter import filedialog
	from tkinter import messagebox
except ImportError:
	# python2
	from Tkinter import Tk, Label, Button, BOTH, Frame, BooleanVar, Checkbutton
	import tkMessageBox as messagebox
	import tkFileDialog as filedialog



class App(Frame):
    def __init__(self, parent):
        Frame.__init__(self, parent)
        self.parent = parent

        self.student_file = None # path to the file containing student info
        self.course_file = None  # path to the file containing course info
        self.save_file = None    # path to save to (CSV file)
        self.var = BooleanVar()
        
        self.initUI()

    def initUI(self):
        """
        Build the UI and hook up the buttons.
        """
        self.parent.title('FYS Assignment')
        self.pack(fill=BOTH, expand=1)
        
        self.student_button = Button(self, text='Browse', command=self.open_students)
        self.student_button.place(x=10, y=40)
        self.student_label = Label(self, text='Student File')
        self.student_label.place(x=100, y=45)

        self.course_button = Button(self, text='Browse', command=self.open_courses)
        self.course_button.place(x=10, y=80)
        self.course_label = Label(self, text='Course File')
        self.course_label.place(x=100, y=85)

        self.save_button = Button(self, text='Browse', command=self.save)
        self.save_button.place(x=10, y=120)
        self.save_label = Label(self, text='Save File')
        self.save_label.place(x=100, y=125)

        self.assign_button = Button(self, text='Assign', command=self.assign)
        self.assign_button.place(x=330, y=150)

        self.check_button = Checkbutton(self, text='Randomize?', variable=self.var)
        self.check_button.place(x=230, y=155)


    def save(self):
        """
        Open a save dialog and get the path name to save to
        """
        save_file_path = filedialog.asksaveasfile()

        # make sure it's a CSV file
        self.save_file = save_file_path.name
        if self.save_file[-4:].lower() != '.csv':
            remove(self.save_file) # delete the file this creates
            self.save_file = self.save_file + '.csv'
        self.save_label['text'] = self.save_file

    def open_students(self):
        """
        Open a file dialog to get the path of the students excel file
        """
        student_file_path = filedialog.askopenfile()
        self.student_label['text'] = student_file_path.name
        self.student_file = student_file_path.name

    def open_courses(self):
        """
        Open a file dialog to get the path of the courses excel file
        """
        courses_file_path = filedialog.askopenfile()
        self.course_label['text'] = courses_file_path.name
        self.course_file = courses_file_path.name

    def show_error_dialog(self, filetype):
        """
        Show an error dialog about a given file
        """
        messagebox.showerror('Error', 'You must select a ' + filetype + ' file')

    def assign(self):
        """
        - Parse the excel files
        - Generate CSV files for the C++ 'assign' program to parse
        - Call the C++ program
        - Inform the user when finished
        """
        # make sure the user selected all the necessary files
        if self.student_file == None:
            self.show_error_dialog('student')
            return
        if self.course_file == None:
            self.show_error_dialog('course')
            return
        if self.save_file == None:
            self.show_error_dialog('save')
            return

        # read through the data in the students excel/csv file
        filename, ext = os.path.splitext(self.student_file)
        if ext == '.csv':
        	student_data = pandas.read_csv(self.student_file).values
        elif ext in '.xlsx':
        	student_data = pandas.read_excel(self.student_file, sheet_name = 0).values
        else:
        	self.showerror('Error', 'File: ', self.student_file, 'could not be read.')

        # the generated CSV file looks like:
        # Last Name,First Name,ID,Number of FYS Picks,Pick1,Pick2,...,PickN
        # Note the lack of spacing between items, enforced by stripping strings
        student_file_path = self.student_file + '-gen'
        with open(student_file_path, 'w') as f:
            for student in student_data:
                last_name = student[0]
                first_name = student[1]
                id_number = str(student[2])
                fys_picks = student[3].split(',')
                f.write(last_name.strip() + ',')
                f.write(first_name.strip() + ',')
                f.write(id_number.strip() + ',')
                f.write(str(len(fys_picks)) + ',')

                for fys_pick in fys_picks[:-1]:
                    f.write(fys_pick.strip() + ',')
                f.write(fys_picks[-1].strip())
                f.write('\n')

        # df = pandas.read_csv(student_file_path)

        # df2 = df.reindex(np.random.permutation(df.index))

        # student_file_path2 = self.course_file + '-gen2'
        # df2.to_csv(courses_file_path2, index=False)

        # read through the data in the courses excel file
        filename, ext = os.path.splitext(self.course_file)
        if ext == '.csv':
        	courses_data = pandas.read_csv(self.course_file).values
        elif ext in '.xlsx':
        	courses_data = pandas.read_excel(self.course_file, sheet_name = 0).values
        else:
        	self.showerror('Error', 'File: ', self.course_file, 'could not be read.')

        # the generated CSV file looks like:
        # FYS Name,Course CRN,Number of slots available
        # Again, note the lack of spacing between items
        courses_file_path = self.course_file + '-gen'
        with open(courses_file_path, 'w') as f:
            for course in courses_data:
                fys_name = course[0]
                crn_number = str(course[1].strip('CRN').strip())
                slots_available = str(course[2])

                f.write(fys_name + ',' + crn_number + ',' + slots_available + '\n')

        df = pandas.read_csv(courses_file_path)

        # old shuffle
        # df2 = df.reindex(np.random.permutation(df.index))

        # shuffle FYS list in Course File in attempt to better distribute choices
        df2 = df.sample(frac=1).reset_index(drop=True)
        courses_file_path2 = self.course_file + '-gen2'
        df2.to_csv(courses_file_path2, index=False)
                
        # set arg for windows or *nix systems
        if os.name == 'nt':
            arg = 'assign.exe'
        else:
            arg = './assign.exe'
        # Call the assignment program with the proper paths, based on ranomization checkbox    
        if self.var.get():
        	ret = call([arg, student_file_path, courses_file_path2, self.save_file])
        else:
        	ret = call([arg, student_file_path, courses_file_path, self.save_file])

        # get rid of the generated files
        remove(student_file_path)
        remove(courses_file_path)
        remove(courses_file_path2)

        # Inform the user that the assignment is finished
        self.done_label = Label(self, text='Done!')
        self.done_label.place(x=10, y=155)

def main():
    root = Tk()
    root.geometry('450x190+300+300')
    app = App(root)
    root.mainloop()
    root.destroy()

if __name__ == '__main__':
    main()
