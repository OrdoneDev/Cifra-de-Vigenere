#include <gtk/gtk.h>
#include <iostream>
using std::string;

GtkWidget *entry_text, *entry_senha;

int getFactor(char c){
    int retorno = 0;
    if (c >= 'A' && c <= 'Z')
        retorno = 65;
    else if (c >= 'a' && c <= 'z')
        retorno = 97;
    return retorno;
}

static void Crypt_click(GtkWidget *widget, gpointer data){
    string msg = gtk_entry_get_text(GTK_ENTRY(entry_text));
    string senha = gtk_entry_get_text(GTK_ENTRY(entry_senha));

    for (int x = 0, y = 0; x < msg.size(); ++x, ++y){
        char cut = msg[x];
        if (cut == ' ')
            continue;

        int msgFactor = getFactor(cut);
        int senhaFactor = getFactor(senha[y]);

        int res = cut+senha[y]-senhaFactor;
        if (res > msgFactor+25)
            res -= 26;

        if ((x >= senha.size()-1) && ((x+1)%senha.size()) == 0)
            y = -1;

        msg[x] = (char)res;
    }
    gtk_label_set_text(GTK_LABEL(data), msg.c_str());
}

static void Decrypt_click(GtkWidget *widget, gpointer data){
    string msg = gtk_entry_get_text(GTK_ENTRY(entry_text));
    string senha = gtk_entry_get_text(GTK_ENTRY(entry_senha));

    for (int x = 0, y = 0; x < msg.size(); ++x, ++y){
        char cut = msg[x];
        if (cut == ' ')
            continue;

        int msgFactor = getFactor(cut);
        int senhaFactor = getFactor(senha[y]);

        int res = cut-senha[y]+senhaFactor;
        if (res < msgFactor)
            res += 26;

        if ((x >= senha.size()-1) && ((x+1)%senha.size()) == 0)
            y = -1;

        msg[x] = res;
    }
    gtk_label_set_text(GTK_LABEL(data), msg.c_str());
}

int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);
	GtkWidget *janela, *lbl_text, *lbl_senha, *btn_cript, *btn_decript, *lbl_result, *vbox1, *vbox2, *vbox3, *hbox;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	lbl_text = gtk_label_new("Texto:");
	lbl_senha = gtk_label_new("Senha:");
	lbl_result = gtk_label_new("Resultado:");
    btn_cript = gtk_button_new_with_mnemonic("_Criptografar");
    btn_decript = gtk_button_new_with_mnemonic("_Descriptografar");
    entry_text = gtk_entry_new();
    entry_senha = gtk_entry_new();
    vbox1 = gtk_vbox_new(0,0);
    vbox2 = gtk_vbox_new(0,0);
    vbox3 = gtk_vbox_new(0,0);
    hbox = gtk_hbox_new(0,0);

    gtk_box_pack_start(GTK_BOX(vbox1), lbl_text,0,0,10);
    gtk_box_pack_start(GTK_BOX(vbox1), lbl_senha,0,0,10);

    gtk_box_pack_start(GTK_BOX(vbox2), entry_text,0,1,0);
    gtk_box_pack_start(GTK_BOX(vbox2), entry_senha,0,1,0);
    gtk_box_pack_start(GTK_BOX(vbox2), lbl_result,0,0,0);

    gtk_box_pack_start(GTK_BOX(vbox3), btn_cript,0,0,0);
    gtk_box_pack_start(GTK_BOX(vbox3), btn_decript,0,0,0);

    gtk_box_pack_start(GTK_BOX(hbox), vbox1,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox), vbox2,1,1,0);
    gtk_box_pack_start(GTK_BOX(hbox), vbox3,0,0,0);

    g_signal_connect(janela, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(btn_cript, "clicked", G_CALLBACK(Crypt_click), (gpointer)lbl_result);
    g_signal_connect(btn_decript, "clicked", G_CALLBACK(Decrypt_click), (gpointer)lbl_result);

    gtk_container_add(GTK_CONTAINER(janela), hbox);
    gtk_window_set_title(GTK_WINDOW(janela), "Cifra de Vigenere");
    gtk_window_set_default_size(GTK_WINDOW(janela), 800,100);
	gtk_widget_show_all(janela);
	gtk_main();
	return 0;
}
