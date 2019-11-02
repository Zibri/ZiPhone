#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
jailbreak (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Jailbreak clicked...\n");
   char jailbreak[50];
   strcpy( jailbreak, "./ziphone -j" );
   system(jailbreak);

}

static void
activation (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Activate clicked...\n");
   char activation[50];
   strcpy( activation, "./ziphone -a" );
   system(activation);

}

static void
unlock (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Unlock clicked...\n");
   char unlock[50];
   strcpy( unlock, "./ziphone -u" );
   system(unlock);

}

static void
erase (GtkWidget *widget,gpointer   data)
{
  g_print ("Erase Baseband clicked...\n");
   char erase[50];
   strcpy( erase, "./ziphone -e" );
   system(erase);
}

static void
downgradebl (GtkWidget *widget,gpointer   data)
{
  g_print ("Downgrade Bootloader clicked...\n");
   char downgradebl[50];
   strcpy( downgradebl, "./ziphone -b" );
   system(downgradebl);
}

static void
debugboot (GtkWidget *widget,gpointer   data)
{
  g_print ("Debug Boot clicked...\n");
   char debugboot[50];
   strcpy( debugboot, "./ziphone -v" );
   system(debugboot);
}

static void
exitrecovery (GtkWidget *widget,gpointer   data)
{
  g_print ("Exit Recovery clicked...\n");
   char exitrecovery[50];
   strcpy( exitrecovery, "./ziphone -N" );
   system(exitrecovery);
}

static void
enterdfu (GtkWidget *widget,gpointer   data)
{
  g_print ("Enter DFU Mode clicked...\n");
   char enterdfu[50];
   strcpy( enterdfu, "./ziphone -D" );
   system(enterdfu);
}

static void
jailbreak_and_activation (GtkWidget *widget,gpointer   data)
{
  g_print ("Jailbreak and Activate clicked...\n");
   char jailbreak_and_activation[50];
   strcpy( jailbreak_and_activation, "./ziphone -j -a" );
   system(jailbreak_and_activation);

}

static void
jailbreak_activation_unlock (GtkWidget *widget,gpointer   data)
{
  g_print ("Jailbreak, Activate, and Unlock clicked...\n");
   char jailbreak_activation_unlock[50];
   strcpy( jailbreak_activation_unlock, "./ziphone -j -a -u" );
   system(jailbreak_activation_unlock);

}

static void
kill_ziphone (GtkWidget *widget,gpointer   data)
{
  g_print ("Kill ZiPhone clicked...\n");
   char kill_ziphone[50];
   strcpy( kill_ziphone, "killall ziphone" );
   system(kill_ziphone);

}

static void
activate (GtkApplication *app, gpointer        user_data)
{
	GtkWidget *window;
	GtkWidget *grid;
   GtkWidget *image;
	GtkWidget *button;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "ZiPhone");
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);

	grid = gtk_grid_new ();
	gtk_grid_set_row_spacing (GTK_GRID (grid), 6);
	gtk_grid_set_column_spacing (GTK_GRID (grid), 6);
	gtk_container_add (GTK_CONTAINER (window), grid);

	GdkColor color;
	if (gdk_color_parse("#000000", &color)) 
	{
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
   }
    
	button = gtk_button_new_with_label ("Jailbreak");
	g_signal_connect (button, "clicked", G_CALLBACK (jailbreak), NULL);

	gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

	button = gtk_button_new_with_label ("Activate");
	g_signal_connect (button, "clicked", G_CALLBACK (activation), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);
 
   button = gtk_button_new_with_label ("Unlock");
	g_signal_connect (button, "clicked", G_CALLBACK (unlock), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);
  
   button = gtk_button_new_with_label ("Jailbreak and Activate");
	g_signal_connect (button, "clicked", G_CALLBACK (jailbreak_and_activation), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);
  
	button = gtk_button_new_with_label ("Jailbreak, Activate, and Unlock");
	g_signal_connect (button, "clicked", G_CALLBACK (jailbreak_activation_unlock), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 3, 1);
  
   button = gtk_button_new_with_label ("Erase Baseband");
   g_signal_connect (button, "clicked", G_CALLBACK (erase), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);
  
   button = gtk_button_new_with_label ("Downgrade Bootloader");
   g_signal_connect (button, "clicked", G_CALLBACK (downgradebl), NULL);

   gtk_grid_attach (GTK_GRID (grid), button, 1, 3, 1, 1);

   button = gtk_button_new_with_label ("Debug Boot");
   g_signal_connect (button, "clicked", G_CALLBACK (debugboot), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);

   button = gtk_button_new_with_label ("Exit Recovery");
   g_signal_connect (button, "clicked", G_CALLBACK (exitrecovery), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 1, 4, 1, 1);
  
   button = gtk_button_new_with_label ("Enter DFU");
   g_signal_connect (button, "clicked", G_CALLBACK (enterdfu), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 2, 4, 1, 1);
   
  button = gtk_button_new_with_label ("Kill ZiPhone");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (kill_ziphone), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 3, 1);

  button = gtk_button_new_with_label ("Exit GUI");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 6, 3, 1);

  gtk_widget_show_all (window);
}

int main (int argc,char **argv)
{
  GtkApplication *app;
  int status;

if(geteuid() != 0)
{
  printf("You must run ./zgui as root or with sudo.\n");
  exit(1);
}

printf("Starting GUI...\n");

  app = gtk_application_new ("com.zibriandlex.ziphone", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
