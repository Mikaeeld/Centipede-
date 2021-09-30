#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
#include <unordered_set>
#include <set>
#include <memory>

using namespace std;

struct KeyFrame
{
	float percent = 0.0f;
	shared_ptr<sf::Texture> texture = nullptr;

	KeyFrame(float p, shared_ptr<sf::Texture> t)
	{
		percent = p;
		texture = t;
	};

	bool operator==(const KeyFrame &rhs) const { return this->percent == rhs.percent; };
	bool operator>(const KeyFrame &rhs) const { return this->percent > rhs.percent; };
	bool operator<(const KeyFrame &rhs) const { return this->percent < rhs.percent; };
};

enum class AnimateMode
{
	loop,
	pause,
	once,
	once_restart
};

class GameEntity : public sf::Sprite
{
public:
	GameEntity();
	GameEntity(float period, float phase);
	~GameEntity() {}

	/**
	 * @brief This method is defined when inherited
	 *
	 * Purpose is to allow GameEntity to update variables, physics ect.
	 * @param time
	 */
	virtual void tick(sf::Time time)
	{ /* default */
		totalTime_ += time.asSeconds();
	}

	/**
	 * @brief Changes the texture of the GameEntity to the relevant one.
	 *
	 * @param time
	 */
	void animateTick(sf::Time time);

	/**
	 * @brief Get the Key Frames object
	 *
	 * @return vector<KeyFrame>
	 */
	set<KeyFrame> getKeyFrames() { return keyFrames_; }

	/**
	 * @brief Returns true if key frames should be updated else renders current keyframe.
	 *
	 * @return true
	 * @return false
	 */
	bool animate() const { return animate_; };

	/**
	 * @brief Adds a Key Frame to the Key Frames object
	 *
	 *  Note this performs a sort on the Key Frames object, hence it should be called when creating the object.
	 *
	 * @param kf
	 */
	void addKeyFrame(KeyFrame &kf) { keyFrames_.insert(kf); }

	/**
	 * @brief Removes any Key Frames matching the input.
	 *
	 * @param kf
	 */
	void removeKeyFrame(float percent);

	/**
	 * @brief Sets the animation Period in seconds
	 *
	 * @param p
	 */
	void setPeriod(float &p)
	{
		period_ = p;
	}

	const float &getPeriod() const
	{
		return period_;
	}

	const float &getAnimateStart() const
	{
		return animateStart_;
	}

	const float &getAnimateEnd() const
	{
		return animateEnd_;
	}

	/**
	 * @brief Set the Animate Start in percentage
	 *
	 * Valid range 0.0 - 100.0
	 *
	 * @param start
	 */
	void setAnimateStart(float &start)
	{
		animateStart_ = start;
	}

	/**
	 * @brief Set the Animate End in percentage
	 *
	 * Valid range 0.0 - 100.0
	 *
	 * @param end
	 */
	void setAnimateEnd(float &end)
	{
		animateEnd_ = end;
	}

	/**
	 * @brief Returns true if the animation has completed its key frame sequence.
	 *
	 * @return true
	 * @return false
	 */
	bool animateDone() const
	{
		return animate_;
	}

	/**
	 * @brief Returns true if this object colides with 'other'.
	 *
	 * @param other
	 * @return true
	 * @return false
	 */
	bool collidesWith(GameEntity &other) const;

	/**
	 * @brief Get the Current Key Frame
	 *
	 * @return const KeyFrame
	 */
	const KeyFrame getCurrentKeyFrame() const;

	/**
	 * @brief Get the Types of the Game Entity
	 *
	 * @return unordered_set<string>
	 */
	unordered_set<string> getTypes() const
	{
		return types_;
	}

	const AnimateMode &getAnimateMode() const { return animateMode_; }

private:
	unordered_set<string> types_;
	bool animate_;
	set<KeyFrame> keyFrames_;
	float period_;
	float animateStart_;
	float animateEnd_;
	size_t currentKeyFrame_;
	float currentTime_;
	AnimateMode animateMode_;
	set<KeyFrame>::iterator itr_;
	float totalTime_;
};