#ifndef HISTCREATOR_H
#define HISTCREATOR_H
class CVImage;
/**
 * @namespace HistCreator
 * @brief HistCreator
 * 
 */
namespace HistCreator {
/**
 * @brief creating hist sessions
 * 
 * @param blank 
 * @param src 
 */
void filled_hist(CVImage& blank, const CVImage& src);
};

#endif // HISTCREATOR_H
