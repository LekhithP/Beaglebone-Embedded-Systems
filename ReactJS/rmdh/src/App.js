import React from 'react'
import Navbar from './components/navbar/navbar'
import Hero from './components/hero/hero'
import Introduce from './components/intro/intro'
import Footer from './components/footer/footer'

function App() {
  return (
    <div>
      <Navbar />
      <Hero />
      <Introduce />
      <Footer />
    </div>
  );
}

export default App;
