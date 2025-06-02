#ifndef TEMPERARYCACHER_H
#define TEMPERARYCACHER_H
 
#include <QMap>
/**
 * @brief 	TemperaryCacher cached the tmp
 *			Markdown holder
 * 
 */
class TemperaryCacher {
public:
	/**
 	* @brief Construct a new Temperary Cacher object
 	* 
 	*/
	TemperaryCacher() = default;
	Q_DISABLE_COPY_MOVE(TemperaryCacher); ///< disabled the TemperaryCacher
	/**
	 * @brief push the label <-> context pair into management
	 * 
	 * @param label 
	 * @param text 
	 */
	void ensub_labels(const QString& label, const QString& text);
	/**
	 * @brief remove the management
	 * 
	 * @param label 
	 */
	void remove_label(const QString& label);
	/**
	 * @brief clear the holdings
	 * 
	 */
	void clear() { label_context_map.clear(); }
	/**
	 * @brief label managings
	 * 
	 * @return QStringList 
	 */
	QStringList labels() const { return label_context_map.keys(); }
	/**
	 * @brief query the context
	 * 
	 * @param label 
	 * @return std::optional<QString> 
	 */
	std::optional<QString> query(const QString& label);

private:
	QMap<QString, QString> label_context_map; ///< holding maps
};

#endif // TEMPERARYCACHER_H
