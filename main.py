import serial
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import mysql.connector

# Confi du port série 
port = 'COM3'  
baudrate = 115200  
# Création de la fenêtre principale de l'IHM
window = tk.Tk()
window.title("IHM STM32")
# Créa labels 
ac_x_label = tk.Label(window, text="ac_x: ")
ac_y_label = tk.Label(window, text="ac_y: ")
ac_z_label = tk.Label(window, text="ac_z: ")
ge_x_label = tk.Label(window, text="ge_x: ")
ge_y_label = tk.Label(window, text="ge_y: ")
ge_z_label = tk.Label(window, text="ge_z: ")
ac_x_label.pack()
ac_y_label.pack()
ac_z_label.pack()
ge_x_label.pack()
ge_y_label.pack()
ge_z_label.pack()



# Configuration de la connexion à la base de données
db_host = 'localhost'
db_user = 'root'
db_password = ''
db_name = 'embproject1'

# Connexion à la base de données
db_connection = mysql.connector.connect(
    host=db_host,
    user=db_user,
    password=db_password,
    database=db_name
)
# Création de la figure pour les tracés
figure = Figure(figsize=(10, 8), dpi=100)
plot_ac = figure.add_subplot(211)
plot_ge = figure.add_subplot(212)
canvas = FigureCanvasTkAgg(figure, master=window)
canvas.get_tk_widget().pack()

# Configuration des données initiales pour les traces
num_points = 100
time = [i for i in range(num_points)]
ac_x_data = [0] * num_points
ac_y_data = [0] * num_points
ac_z_data = [0] * num_points
ge_x_data = [0] * num_points
ge_y_data = [0] * num_points
ge_z_data = [0] * num_points

# Tracés initiaux
line_ac_x, = plot_ac.plot(time, ac_x_data, label='ac_x')
line_ac_y, = plot_ac.plot(time, ac_y_data, label='ac_y')
line_ac_z, = plot_ac.plot(time, ac_z_data, label='ac_z')
plot_ac.set_title('Accélération')
plot_ac.set_xlabel('Temps')
plot_ac.set_ylabel('Valeur')
plot_ac.legend()

line_ge_x, = plot_ge.plot(time, ge_x_data, label='ge_x')
line_ge_y, = plot_ge.plot(time, ge_y_data, label='ge_y')
line_ge_z, = plot_ge.plot(time, ge_z_data, label='ge_z')
plot_ge.set_title('Gyroscope')
plot_ge.set_xlabel('Temps')
plot_ge.set_ylabel('Valeur')
plot_ge.legend()

# Fonction pour mettre à jour les labels et les tracés
def update_labels_plots():
    # Lecture des données depuis le port série
    line = ser.readline().decode('utf-8').strip()
    values = line.split('\t')

    if len(values) == 6:
        try:
            # Extraction des valeurs d'accélération et de gyroscope
            ac_x = float(values[0].split(':')[1])*8.0/32768.0
            ac_y = float(values[1].split(':')[1])*8.0/32768.0
            ac_z = float(values[2].split(':')[1])*8.0/32768.0
            ge_x = float(values[3].split(':')[1])*2000.0/32768.0
            ge_y = float(values[4].split(':')[1])*2000.0/32768.0
            ge_z = float(values[5].split(':')[1])*2000.0/32768.0

            # Mettre à jour les labels avec les nouvelles valeurs
            ac_x_label.config(text="ac_x: {}".format(ac_x))
            ac_y_label.config(text="ac_y: {}".format(ac_y))
            ac_z_label.config(text="ac_z: {}".format(ac_z))
            ge_x_label.config(text="ge_x: {}".format(ge_x))
            ge_y_label.config(text="ge_y: {}".format(ge_y))
            ge_z_label.config(text="ge_z: {}".format(ge_z))





            # Mettre à jour les données pour les tracés
            ac_x_data.pop(0)
            ac_x_data.append(ac_x)
            ac_y_data.pop(0)
            ac_y_data.append(ac_y)
            ac_z_data.pop(0)
            ac_z_data.append(ac_z)

            ge_x_data.pop(0)
            ge_x_data.append(ge_x)
            ge_y_data.pop(0)
            ge_y_data.append(ge_y)
            ge_z_data.pop(0)
            ge_z_data.append(ge_z)

            # Mettre à jour les tracés
            line_ac_x.set_ydata(ac_x_data)
            line_ac_y.set_ydata(ac_y_data)
            line_ac_z.set_ydata(ac_z_data)

            line_ge_x.set_ydata(ge_x_data)
            line_ge_y.set_ydata(ge_y_data)
            line_ge_z.set_ydata(ge_z_data)


            # Mettre à jour l'échelle des tracés
            plot_ac.set_ylim(-4, 4)
            plot_ge.set_ylim(-5000, 5000)

            # Tracer les valeurs d'accélération
           # plot_ac.clear()
            #plot_ac.plot([0, 1, 2], [ac_x, ac_y, ac_z], label='Accélération (ac_x, ac_y, ac_z)')
            #plot_ac.set_title('Accélération')
            #plot_ac.set_xlabel('Temps')
            #plot_ac.set_ylabel('Valeur')
            #plot_ac.legend()

            # Tracer les valeurs de gyroscope
            #plot_ge.clear()
            #plot_ge.plot([0, 1, 2], [ge_x, ge_y, ge_z], label='Gyroscope (ge_x, ge_y, ge_z)')
            #plot_ge.set_title('Gyroscope')
            #plot_ge.set_xlabel('Temps')
            #plot_ge.set_ylabel('Valeur')
            #plot_ge.legend()
            # Mettre à jour le graphique
            canvas.draw()
            # Insertion des données dans la base de données
            db_cursor = db_connection.cursor()
            insert_query = "INSERT INTO acge1 (acx1, acy1, acz1, gex1, gey1, gez1) VALUES (%s, %s, %s, %s, %s, %s)"
            insert_values = (ac_x, ac_y, ac_z, ge_x, ge_y, ge_z)
            db_cursor.execute(insert_query, insert_values)
            db_connection.commit()

        except ValueError:
            pass
    # Planifier la prochaine mise à jour
    window.after(100, update_labels_plots)

# connexion série
try:
    ser = serial.Serial(port, baudrate)
    print("Connexion série établie sur le port", port)
except serial.SerialException:
    print("Erreur lors de l'ouverture de la connexion série sur le port", port)
    exit(1)

# Démarrage de la mise à jour des labels et des tracés
update_labels_plots()

# Lancement de la boucle principale de l'IHM
window.mainloop()

# Fermeture de la connexion série à la sortie de l'IHM
ser.close()
