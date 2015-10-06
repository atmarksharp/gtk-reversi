#include <stdio.h>
#include <gtk/gtk.h>

#define DEBUG

#define TITLE "GTK REVERSI"
#define TITLE_IMAGE "title.png"
#define MENU_WINDOW_W 400
#define MENU_WINDOW_H 200

GtkWidget *menuWin;
GtkWidget *okDlg;

void set_margin(GtkWidget* widget, gint margin){
  gtk_widget_set_margin_start(widget, margin);
  gtk_widget_set_margin_end(widget, margin);
  gtk_widget_set_margin_top(widget, margin);
  gtk_widget_set_margin_bottom(widget, margin);
}

void responseDialog(GtkDialog *dialog, gint response){
  gtk_dialog_response(dialog, response);
  return;
}

void responseOK(){
  gtk_dialog_response(GTK_DIALOG(okDlg), GTK_RESPONSE_OK);
}

void okDialog(const gchar *message, const gchar *title){
  GtkWidget *content_area, *box, *msgLbl, *okBtn;
  okDlg = gtk_dialog_new ();
  gtk_window_set_title(GTK_WINDOW(okDlg), title);
  gtk_window_set_default_size(GTK_WINDOW(okDlg), 200, 100);

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (okDlg));

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  set_margin(box, 10);
  gtk_box_set_center_widget(GTK_BOX(content_area), box);

  msgLbl = gtk_label_new (message);
  gtk_container_add(GTK_CONTAINER(box), msgLbl);

  okBtn = gtk_button_new_with_label ("OK");
  gtk_container_add(GTK_CONTAINER(box), okBtn);

  g_signal_connect(okBtn, "clicked", G_CALLBACK(responseOK), NULL);
  g_signal_connect_swapped (okDlg, "response", G_CALLBACK (gtk_widget_destroy), okDlg);

  gtk_widget_show (okBtn);
  gtk_widget_show (msgLbl);
  gtk_widget_show (box);
  gtk_dialog_run (GTK_DIALOG(okDlg));
  return;
}

void notImplementedDialog(){
  okDialog("Not Implemented, sorry", "alert");
  return;
}

void showStartMenu(){

  // Create Menu Window ===============================

  menuWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(menuWin), MENU_WINDOW_W, MENU_WINDOW_H);
  gtk_window_set_title(GTK_WINDOW(menuWin), TITLE);
  gtk_window_set_position (GTK_WINDOW(menuWin), GTK_WIN_POS_CENTER);

  g_signal_connect (menuWin, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  // Add contents ===============================

  GtkWidget *wrapper;
  wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(menuWin), wrapper);

  GtkWidget *container;
  container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_set_center_widget(GTK_BOX(wrapper), container);
  set_margin(container, 20);

  GtkWidget *titleImg;
  titleImg = gtk_image_new_from_file (TITLE_IMAGE);
  gtk_container_add(GTK_CONTAINER(container), titleImg);

  GtkWidget *selectLbl;
  selectLbl = gtk_label_new (NULL);
  gtk_label_set_markup(GTK_LABEL(selectLbl), "<span font_weight=\"bold\" size=\"large\">[ please select ]</span>");
  gtk_container_add(GTK_CONTAINER(container), selectLbl);

  GtkWidget *onePlayerBtn;
  onePlayerBtn = gtk_button_new_with_label ("1 player");
  g_signal_connect (onePlayerBtn, "clicked", G_CALLBACK (notImplementedDialog), NULL);
  gtk_container_add(GTK_CONTAINER(container), onePlayerBtn);

  GtkWidget *twoPlayerBtn;
  twoPlayerBtn = gtk_button_new_with_label ("2 players");
  g_signal_connect (twoPlayerBtn, "clicked", G_CALLBACK (gameStart), NULL);
  gtk_container_add(GTK_CONTAINER(container), twoPlayerBtn);

  // Start GTK ===============================

  gtk_widget_show (twoPlayerBtn);
  gtk_widget_show (onePlayerBtn);
  gtk_widget_show (selectLbl);
  gtk_widget_show (titleImg);
  gtk_widget_show (container);
  gtk_widget_show (wrapper);
  gtk_widget_show (menuWin);
  gtk_main ();

  return;
}

int main(int argc, char *argv[]){
  gtk_init(&argc, &argv);
  showStartMenu();

  return 0;
}
