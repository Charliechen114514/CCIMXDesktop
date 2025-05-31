#ifndef DISKMUSIC_H
#define DISKMUSIC_H
#include <QTimer>
#include <QWidget>
class QPropertyAnimation;
class QVariantAnimation;
namespace Ui {
class DiskMusic;
}

/**
 * @brief The DiskMusic class is a Widget Class(Sorry for the non-class label)
 * that holding all the details of the disk eyes level interative
 */
class DiskMusic : public QWidget {
	Q_OBJECT
	/**
	 * @brief property announced
	 */
	Q_PROPERTY(qreal armAngle READ armAngle WRITE setArmAngle NOTIFY armAngleChanged);
	static constexpr const unsigned int ANIMATION_DURATION = 300; ///< animation duration
	static constexpr const unsigned int ANIMATION_FPS = 60; ///< animation fps, that means how fluent the animations is
	static constexpr const qreal BEGIN_ANGLE = -30; ///< the arm angle begins
	static constexpr const qreal END_ANGLE = -10; ///< the arm angle ends
	static constexpr const unsigned int SWITCH_COLOR_MSEC_INTERVAL = 20000; ///< the interval to switch color, in msecs level
	static constexpr const unsigned int COLOR_SWITCH_PROCESS_INTERVAL = 2000; ///< the interval to switch color, in msecs level

	/* every time the default color media first open */
	static constexpr const QColor BEGIN_COLOR = QColor(173, 216, 230); ///< the begin color of background for linear gradient
	static constexpr const QColor END_COLOR = QColor(0, 51, 102); ///< the end color of background for linear gradient

public:
	/**
	 * @brief Construct a new Disk Music object
	 * 
	 * @param parent 
	 */
	explicit DiskMusic(QWidget* parent = nullptr);

	/**
	 * @brief setStatus set the status of the disk
	 * @param set_is_playing the status to set, when
	 * the status changed, the animations status changed
	 */
	void setStatus(bool set_is_playing);

	/**
	 * @brief setPixmap set the pixmap of the disk center display
	 * @param pixmap_path the path to the pixmap
	 */
	void setPixmap(const QString& pixmap_path);

	/**
	 * @brief armAngle get the arm angle
	 * @return the arm angle
	 */
	inline qreal armAngle() const {
		return angle;
	}

	/**
	 * @brief setArmAngle set the arm angle
	 * @param angle the angle to set
	 */
	inline void setArmAngle(qreal angle) {
		this->angle = angle;
		update();
		emit armAngleChanged();
	}

	/**
	 * @brief Destroy the Disk Music object
	 * 
	 */
	~DiskMusic();

signals:
	/**
	 * @brief armAngleChanged the signal indicating the arm angle changed
	 * @note this is the signal for the animation to update
	 */
	void armAngleChanged();

protected:
	/**
	 * @brief paintEvent the paint event for the disk
	 * @param event the paint event
	 */
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::DiskMusic* ui; ///< ui handle
	qreal angle { BEGIN_ANGLE }; ///< the arm angle
	float current_rotations {}; ///< the current rotations
	bool is_playing { false }; ///< the status of the disk
	QTimer animate_timer; ///< the timer to animate the disk
	QPropertyAnimation* animation { nullptr };
	QVariantAnimation* color_animation { nullptr };

	struct {
		QPixmap coverPixmap; ///< the cover pixmap
		QPixmap armPixmap; ///< the arm pixmap
		QPixmap recordPixmap; ///< the record pixmap
	} pixmaps; ///< the pixmaps to display
	void initUi();
	void initCore();

	/**
	 * @brief process_rotation process the rotation of the disk
	 */
	void process_rotation() {
		current_rotations += 0.5;
		if (current_rotations >= 360.0)
			current_rotations -= 360.0;
		update();
	}
	/* for current varient change */
	void process_the_color_change(QPainter& p);
	void startColorTransition();

	QColor beginColor { BEGIN_COLOR };
	QColor endColor { END_COLOR };
	QColor targetStart;
	QColor targetEnd;

	QTimer color_switch_timer;
};

#endif // DISKMUSIC_H
