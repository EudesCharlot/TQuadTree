#pragma once
//Evidemment, il va falloir inclure les fichiers nécessaires pour que le code compile
#include <vector>

//Vous n'avez pas le droit de modifier cette partie du code jusqu'à la ligne notée par le commentaire //Vous pouvez modifier le code ci-dessous
#include <concepts>
#include <stdexcept>

/**
 * @brief Concept définissant les exigences pour les données pouvant être stockées dans un TQuadTree.
 *
 * Ce concept vérifie que le type T possède les méthodes x1(), y1(), x2() et y2() qui retournent des valeurs convertibles en float.
 * De plus, le type T doit être copiable et comparable pour l'égalité.
 *
 * @tparam T Le type des données à vérifier.
 *
 * Les exigences pour le type T sont les suivantes :
 * - T doit avoir une méthode x1() retournant un type convertible en float.
 * - T doit avoir une méthode y1() retournant un type convertible en float.
 * - T doit avoir une méthode x2() retournant un type convertible en float.
 * - T doit avoir une méthode y2() retournant un type convertible en float.
 * - T doit être copiable.
 * - T doit être comparable pour l'égalité.
 */
template<typename T>
concept QuadTreeData = requires(T t)
{
    { t.x1() } -> std::convertible_to<float>;
    { t.y1() } -> std::convertible_to<float>;
    { t.x2() } -> std::convertible_to<float>;
    { t.y2() } -> std::convertible_to<float>;
}&& std::copyable<T>&& std::equality_comparable<T>;

/**
 * @brief Structure définissant les limites d'une zone rectangulaire.
 */
struct SLimits
{
    float x1; ///< La coordonnée x du coin supérieur gauche.
    float y1; ///< La coordonnée y du coin supérieur gauche.
    float x2; ///< La coordonnée x du coin inférieur droit.
    float y2; ///< La coordonnée y du coin inférieur droit.

    bool operator==(const SLimits& other) const = default;
};

/**
 * @brief Classe de QuadTree.
 *
 * Cette classe permet de stocker des données de type T dans un QuadTree.
 *
 * @tparam T Le type des données à stocker.
 * T doit respecter le concept QuadTreeData.
 */
template <QuadTreeData T>
class TQuadTree
{
    //Vous pouvez modifier le code ci-dessous
    //Attention à ne pas modifier les signatures des fonctions et des méthodes qui sont déjà présentes
public:
    using container = std::vector<T>;

    //Données membres
private:
    SLimits m_limits;
    container m_data;
    std::unique_ptr<TQuadTree> m_children[4];

    /**
      * @brief Itérateur pour parcourir les éléments du QuadTree.
      */
    class iterator {
    public:
        //Ces typedefs sont nécessaires pour que l'itérateur soit reconnu comme un itérateur d'entrée
        //par les algorithmes de la STL. Vous ne devriez pas les modifier.
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::input_iterator_tag;

    private:

    public:
        /**
         * @brief Constructeur par défaut de l'itérateur.
         *
         * Evidemment, il va falloir compléter cette fonction pour qu'elle initialise correctement l'itérateur.
         * Peut-être que l'itérateur devrait être initialisé à la fin de la liste de données.
         * Peut-etre qu'on peut ajouter d'autres constructeurs pour initialiser l'itérateur à un endroit spécifique.
         */
        iterator() = default;

        /**
         * @brief Opérateur de comparaison d'égalité.
         *
         * @returns true si les deux itérateurs sont à la même position.
         */
        bool operator==(const iterator& other) const
        {
            //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne true si les deux itérateurs sont à la même position
            return true;
        }

        /**
         * @brief Opérateur de pré-incrémentation de l'itérateur.
         *
         * @returns l'itérateur courant avancé vers la prochaine position valide.
         */
        iterator& operator++()
        {
            //Evidemment, il va falloir compléter cette fonction pour qu'elle avance l'itérateur à la prochaine position valide
            return *this;
        }

        /**
         * @brief Opérateur de post-incrémentation de l'itérateur.
         *
         * @param int Un paramètre fictif pour distinguer l'opérateur de pré-incrémentation de celui-ci.
         *
         * @returns l'itérateur courant avant d'être avancé vers la prochaine position valide.
         */
        iterator operator++(int)
        {
            //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne l'itérateur courant avant d'être avancé
            return {};
        }

        /**
         * @brief Opérateur de déréférencement de l'itérateur.
         *
         * @returns une référence vers l'élément pointé par l'itérateur.
         */
        T& operator*() const
        {
            throw std::logic_error("Not implemented yet");
        }

        T* operator->()
        {
            return &(this->operator*());
        }
    };


public:
    /**
     * @brief Constructeur de la classe TQuadTree.
     *
     * @param limits Les limites géométriques du QuadTree.
     */
    TQuadTree(const SLimits& limits = { 0.0f,0.0f,1.0f,1.0f })
    {
        //Evidemment, il va falloir compléter ce constructeur pour qu'il initialise correctement votre TQuadTree
        m_limits = limits;
        for (auto& child : m_children) {
            child = nullptr;
        }
    }

    //Constructeur par copie
    TQuadTree(const TQuadTree& Other) {
        m_limits = Other.m_limits;
        m_data = Other.m_data;
        for (size_t i = 0; i < 4; ++i) {
            if (Other.m_children[i]) {
                m_children[i] = std::make_unique<TQuadTree>(*Other.m_children[i]);
            }
            else {
                m_children[i] = nullptr;
            }
        }
    }

    /**
     * @brief Retourne les limites géométriques de ce QuadTree
     */
    SLimits limits() const
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne les limites géométriques de ce QuadTree
        return m_limits;
    }

    /**
     * @brief Vérifie si le QuadTree est vide.
     *
     * Cette fonction vérifie si le QuadTree ne contient aucun élément de données, y compris dans la descendance.
     *
     * @return true si le QuadTree est vide, false sinon.
     */
    bool empty() const
    {
        if (!m_data.empty()) {
            return false;
        }
        for (const auto& child : m_children) {
            if (child && !child->empty()) {
                return false;
            }
        }
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne true uniquement si le QuadTree est vide
        return true;
    }

    /**
     * @brief Retourne la profondeur maximale du QuadTree.
     *
     * La profondeur maximale du QuadTree correspond nombre maximal de niveaux de descendants.
     */
    size_t depth() const
    {
        size_t maxDepth = 0;
        for (size_t i = 0; i < 4; i++) {
            if (m_children[i]) {
                maxDepth = std::max(maxDepth, m_children[i]->depth());
            }
        }

        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne la profondeur maximale du QuadTree
    return 1+maxDepth;
    }

    /**
     * @brief Retourne le nombre d'éléments stockés dans le QuadTree.
     *
     * Cette fonction retourne le nombre d'éléments stockés dans le QuadTree en incluant toute la descendance.
     *
     * @return Le nombre d'éléments stockés dans le QuadTree.
     */
    size_t size() const
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne le nombre d'éléments stockés dans le QuadTree
      size_t totalSize= m_data.size();

        for (const auto& child : m_children)
            if (child)
                totalSize += child->size();

        return totalSize;
    }

    /**
     * @brief Insère un élément dans le QuadTree.
     *
     * Cette fonction insère un élément de données dans le QuadTree.
     * Si l'élément est en dehors des limites du QuadTree, une exception de type std::domain_error est levée.
     * Si l'élément est dans les limites d'un enfant, il est inséré dans cet enfant.
     * Sinon, l'élément est ajouté à la liste des données du QuadTree.
     *
     * @param t L'élément à insérer dans le QuadTree.
     */
    void insert(const T& t)
    {
        if (BiggerThanLimits(t, m_limits)) {
            throw std::domain_error("L objet a inserer ne rentre pas dans la taille du TQuadTree");
        }
        if (BiggerThanHalfLimits(t, m_limits)) {
            m_data.push_back(t);
        }
        else {
            subdivide(t);
        }
        //Evidemment, il va falloir compléter cette fonction pour qu'elle insère l'élément dans le QuadTree
    }
    bool BiggerThanLimits(const T& t, SLimits limits) {
        if (t.x1() < limits.x1 || t.y1() < limits.y1 || t.x2() > limits.x2 || t.y2() > limits.y2) {
            return true;
        }
        return false;

    }
    bool BiggerThanHalfLimits(const T& t, SLimits limits) {
        if (t.x2() - t.x1() > (limits.x2 - limits.x1) / 2 || t.y2() - t.y1() > (limits.y2 - limits.y1) / 2) {
            return true;
        }
        return false;
    }

    //La fonction subdivide est là pour permettre dans le cas où un objet est plus petit que la moitié des limites du parent.
    // Elle créé les TQuadTree enfants de façon récursive (appel de insert) jusqu'à que l'objet t soit contenu dans les limites d'un children et donc ajouté au m_data du children
    void subdivide(const T& t)
    {
        float midX = (m_limits.x1 + m_limits.x2) / 2.0f;
        float midY = (m_limits.y1 + m_limits.y2) / 2.0f;

        if (!m_children[0]) {
            m_children[0] = std::make_unique<TQuadTree>(SLimits{ m_limits.x1, m_limits.y1, midX, midY });
            m_children[1] = std::make_unique<TQuadTree>(SLimits{ midX, m_limits.y1, m_limits.x2, midY });
            m_children[2] = std::make_unique<TQuadTree>(SLimits{ m_limits.x1, midY, midX, m_limits.y2 });
            m_children[3] = std::make_unique<TQuadTree>(SLimits{ midX, midY, m_limits.x2, m_limits.y2 });
        }
        for (int i = 0; i < 4; ++i) {
            if (!BiggerThanLimits(t, m_children[i]->m_limits)) {
                m_children[i]->insert(t);
                return;
            }
        }
    }

    /**
     * @brief Vide le QuadTree.
     *
     * Cette fonction vide le QuadTree de toutes ses données.
     */
    void clear()
    {
        m_data.clear();
        for (auto& child : m_children) {
            child = nullptr;
        }
        //Evidemment, il va falloir compléter cette fonction pour qu'elle vide le QuadTree
    }

    void remove(const T& t)
    {
        if (t.x2() < m_limits.x1 || t.x1() > m_limits.x2 || t.y2() < m_limits.y1 || t.y1() > m_limits.y2)
        {
            throw std::domain_error("L objet a supprimer ne rentre pas dans la taille du TQuadTree");
        }

        if (m_children[0])
        {
            for (auto& child : m_children)
            {
                if (child)
                {
                    child->remove(t);
                }
            }
        }

        auto it = std::find(m_data.begin(), m_data.end(), t);
        if (it != m_data.end())
        {
            m_data.erase(it);
        }

        bool allChildrenEmpty = true;
        for (const auto& child : m_children)
        {
            if (child && !child->empty())
            {
                allChildrenEmpty = false;
                break;
            }
        }

        if (allChildrenEmpty)
        {
            for (auto& child : m_children)
            {
                child.reset();
            }
        }
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retire l'élément du QuadTree
    }


    /**
     * @brief Récupère tous les éléments stockés dans le QuadTree.
     *
     * Cette fonction retourne une liste de tous les éléments stockés dans le QuadTree,
     * y compris ceux stockés dans les enfants.
     *
     * @return Une liste de tous les éléments stockés dans le QuadTree.
     */
    container getAll() const {
        container allElement = m_data;

        for (const auto& child : m_children) {
            if (child) {
                container childElements = child->getAll();
                allElement.insert(allElement.end(), childElements.begin(), childElements.end());
            }
        }
        return allElement;
    }

    /**
     * @brief Trouve les éléments dans une zone spécifiée.
     *
     * Cette fonction recherche et retourne une liste de tous les éléments stockés dans le QuadTree
     * qui se trouvent totalement inclus dans la zone spécifiée par limits.
     *
     * @param limits Les limites de la zone de recherche.
     * @return Une liste de tous les éléments trouvés dans la zone spécifiée.
     */
    container findInscribed(const SLimits& limits) const
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne tous les éléments inclus dans la zone spécifiée
        container result;

        if (m_limits.x1 >= limits.x1 && m_limits.x2 <= limits.x2 && m_limits.y1 >= limits.y1 && m_limits.y2 <= limits.y2) {
            result.insert(result.end(), m_data.begin(), m_data.end());
        }
        else {
            for (const auto& element : m_data) {
                if (element.x1() >= limits.x1 && element.x2() <= limits.x2 && element.y1() >= limits.y1 && element.y2() <= limits.y2) {
                    result.push_back(element);
                }
            }
        }

        for (const auto& child : m_children) {
            if (child) {
                container childResult = child->findInscribed(limits);
                result.insert(result.end(), childResult.begin(), childResult.end());
            }
        }
        return result;
    }

    /**
     * @brief Trouve les éléments dans une zone spécifiée.
     *
     * Cette fonction recherche et retourne une liste de tous les éléments stockés dans le QuadTree
     * qui sont en collision avec la zone spécifiée par limits.
     *
     * @param limits Les limites de la zone de recherche.
     * @return Une liste de tous les éléments trouvés dans la zone spécifiée.
     */
    container findColliding(const SLimits& limits) const
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne tous les éléments en collision avec la zone spécifiée
        container collidingElements;

        if (limits.x2 < m_limits.x1 || limits.x1 > m_limits.x2 || limits.y2 < m_limits.y1 || limits.y1 > m_limits.y2) {
            return collidingElements;
        }

        for (const auto& element : m_data) {
            if (element.x1() <= limits.x2 && element.x2() >= limits.x1 && element.y1() <= limits.y2 && element.y2() >= limits.y1) {
                collidingElements.push_back(element);
            }
        }

        for (const auto& child : m_children) {
            if (child) {
                auto childCollisions = child->findColliding(limits);
                collidingElements.insert(collidingElements.end(), childCollisions.begin(), childCollisions.end());
            }
        }
        return collidingElements;
    }

    /**
     * @brief Retourne un iterateur permettant de lister un à un tous les éléments
     */
    iterator begin()
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne un iterateur de début
        return {};
    }

    /**
     * @brief Retourne un iterateur permettant de lister un à un tous les éléments inclus dans les limites spécifiées
     *
     * Les éléments listés sont ceux qui entrent en collision avec les limites spécifiées
     */
    iterator beginColliding(const SLimits& limits)
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne un iterateur de début
        return {};
    }

    /**
     * @brief Retourne un iterateur permettant de lister un à un tous les éléments inclus dans les limites spécifiées
     *
     * Les éléments listés sont ceux qui sont inclus dans les limites spécifiées
     */
    iterator beginInscribed(const SLimits& limits)
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne un iterateur de début
        return {};
    }

    /**
     * @brief Retourne un iterateur de fin
     */
    iterator end()
    {
        //Evidemment, il va falloir compléter cette fonction pour qu'elle retourne un iterateur de fin
        return {};
    }

};

