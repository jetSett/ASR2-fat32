#include <stdbool.h>

/* Structure opaque utilisée par les fonctions de ce fichier. */
struct fat32_driver;

/* Structure opaque utilisée pour représenter un dossier. */
struct fat32_node;

/* Une liste chainée de nœuds. */
struct fat32_node_list {
    struct fat32_node *node; /* Le nœud porté par ce maillon */
    struct fat32_node_list *next; /* Le maillon suivant (ou NULL) */
};
void fat32_node_list_free(struct fat32_node_list *list);

/* Crée une nouvelle structure "fat32_driver" à partir du nom d'un
 * fichier contenant une image FAT32. */
struct fat32_driver* fat32_driver_new(const char *image_name);

/* Libère la mémoire utilisée par une structure "fat32_driver". */
void fat32_driver_free(struct fat32_driver *driver);

/* Renvoie le fat32_node correspondant au dossier racine de l'image disque. */
struct fat32_node* fat32_driver_get_root_dir(const struct fat32_driver *driver);

const char* fat32_node_get_name(const struct fat32_node *node);
bool fat32_node_is_dir(const struct fat32_node *node);

/* Si le nœud 'node' est un dossier, retourne une liste de fat32_node,
 * qui correspondent aux nœuds enfants de celui-ci. */
struct fat32_node_list* fat32_node_get_children(const struct fat32_node *node);

/* Récupère le nœud correspondant à un chemin relatif à un autre nœud.
 * Renvoie NULL si aucun nœud ne correspond. */
struct fat32_node* fat32_node_get_path(const struct fat32_node *node, const char *path);

/* Lit le contenu d'un fichier et l'écrit dans un descripteur de fichier
 * (par exemple stdout). */
void fat32_node_read_to_fd(const struct fat32_node *node, FILE *fd);

/* Libère la mémoire utilisée par une structure "fat32_node". */
void fat32_node_free(struct fat32_node *dir);
