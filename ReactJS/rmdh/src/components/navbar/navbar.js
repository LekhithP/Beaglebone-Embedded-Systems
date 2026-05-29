import React from 'react'
import { LiaPersonBoothSolid } from 'react-icons/lia'
import './navbarstyle.css'
import RM from '../../assets/RM.png'

function Navbar() {
    return (
      <div className='navbar'>
        <div className='logo'>
          <img src={RM} alt="/">
          </img>
        </div>
        <div className="nav-icon">
            <LiaPersonBoothSolid className='icon'/>
        </div>
      </div>
    );
}

export default Navbar