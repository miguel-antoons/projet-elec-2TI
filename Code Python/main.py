import serial # pip install pyserial
from termcolor import colored
from tkinter import *

class MyApp:
    def __init__(self):
        self.window = Tk()
        self.window.title("My Application")
        self.window.geometry("720x480")
        self.window.minsize(480, 360)
        self.window.config(background='#41B77F')

        # modification de texte
        self.text = StringVar()
        self.text.set("")
        self.text_warning = StringVar()
        self.text_warning.set("")
        # initialization des composants
        self.frame = Frame(self.window, bg='#41B77F')

        # Nombre de personne maximum
        self.text_counter = StringVar()
        self.text_counter.set("3")
        self.counter = 3
        
        # nombre de personne dans la pièce
        self.com = 0

        # creation des composants
        self.create_widgets()
        self.update_text()

        # empaquetage
        self.frame.pack(expand=YES)

    # Création de tous les composants
    def create_widgets(self):
        self.create_button_delete()
        self.create_button_add()
        self.create_title()  
        self.create_msg_max() 
        self.create_person_max()
        self.create_msg()
        self.create_person()
        self.create_warning()
        self.window.after(1500, self.update_text)

    # Crétion du titre
    def create_title(self):
        label_title = Label(self.frame, text="Pojet elec 2021", font=("Courrier", 40), bg='#41B77F',
                            fg='white')
        label_title.pack()

    # Creation du bouton -
    def create_button_delete(self):
        button = Button(self.frame, text="-", font=("Courrier", 15), bg='white', fg='#41B77F',
                           command=self.delete_person, width=4, height=2)
        button.pack(side=LEFT, padx=10, pady=10)

    # décrémente le nombre de personne maximum dans la pièce 
    def delete_person(self):
        if self.counter > 1:
            self.counter -= 1
            self.text_counter.set(self.counter)

    # Creation du bouton +
    def create_button_add(self):
        button = Button(self.frame, text="+", font=("Courrier", 15), bg='white', fg='#41B77F',
                           command=self.add_person, width=4, height=2)
        button.pack(pady=25, fill=X, side=RIGHT)

    # incrémente le nombre de personne maximum dans la pièce 
    def add_person(self):
        self.counter += 1
        self.text_counter.set(self.counter)

    # Création du message
    def create_msg_max(self):
        label_msg = Label(self.frame, text="Nombre de personne maximum : ", font=("Courrier", 20), bg='#41B77F',
                               fg='white')
        label_msg.pack()

    # Création du nombre de personne
    def create_person_max(self):
        label_person = Label(self.frame, textvariable=self.text_counter, font=("Courrier", 30), bg='#41B77F',
                               fg='white', height="3")
        label_person.pack()


    # Création du message
    def create_msg(self):
        label_msg = Label(self.frame, text="Nombre de personne dans la pièce : ", font=("Courrier", 20), bg='#41B77F',
                               fg='white')
        label_msg.pack()

    # Création du nombre de personne
    def create_person(self):
        label_person = Label(self.frame, textvariable=self.text, font=("Courrier", 30), bg='#41B77F',
                               fg='white')
        label_person.pack()

    # Création du message warning
    def create_warning(self):
        label_warning = Label(self.frame, textvariable=self.text_warning, font=("Courrier", 10), bg='#41B77F',
                               fg='red')
        label_warning.pack()

    # foncion qui permet de mettre à jour le nombre de personne dans la pièce
    def update_text(self):
        ser = serial.Serial('COM3', baudrate=9600, timeout=1)
        com = ser.readline().decode('ascii')

        if len(com) != 0:
            self.com = com
            # Si le nombre de personne est plus grand que 3 : 
            # un message attention s'affiche
            # La led rouge sur le PIC s'allume
            if int(com) > self.counter:
                # Message 'warning'
                self.text.set(com)
                self.text_warning.set("Attention Il y a trop de personnes dans la pièce")
                print(colored(f"Attention : Il y a {com} personnes dans la pièce", 'red'))

                # permet d'allumer la led rouge 
                ser.write(b"1") 
                    
            else: 
                # permet d'enlever le message 'warning'
                self.text.set(com)
                self.text_warning.set("")
                print(colored(f"Il y a {com} personnes dans la pièce" if int(com) > 1 else f"Il y a {com} personne dans la pièce", 'green'))
                
                # permet d'allumer la led verte
                ser.write(b"0") 

        self.window.after(1500, self.update_text)

if __name__ == "__main__":
    app = MyApp()
    app.window.mainloop()