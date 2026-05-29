import React from 'react'
import './herostyles.css'
import I8 from '../../assets/I8.png'

function Hero() {
    return (
        <div className="hero-container">
            <div className="gradientBackground">
            </div>
            <div className="overlay">
            </div>
            <div className="content">
                <div className="content-img">
                    <img src={I8} alt="/">
                    </img>
                </div>
                <form className="form">
                    <div>
                        <input type="text" placeholder='Enter your dining hall'/>
                    </div>
                    <div>
                        <button>
                        </button>
                    </div>
                </form>
            </div>
        </div>
    )
}

export default Hero