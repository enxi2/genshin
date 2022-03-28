import React from "react";
import ReactDOM from "react-dom";
import { HashRouter, Route, Routes } from "react-router-dom";

import App from "./App";
import Elites from "./pages/Elites";
import FastElites from "./pages/FastElites";
import WishStats from "./pages/WishStats";

import "./index.css";

ReactDOM.render(
  <React.StrictMode>
    <HashRouter>
      <Routes>
        <Route path="/elites" element={<Elites />} />
        <Route path="/fastelites" element={<FastElites />} />
        <Route path="/wishstats" element={<WishStats />} />
        <Route path="/" element={<App />} />
      </Routes>
    </HashRouter>
  </React.StrictMode>,
  document.getElementById("root")
);
