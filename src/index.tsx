import React from "react";
import ReactDOM from "react-dom";
import { HashRouter, Route, Routes } from "react-router-dom";

import App from "./App";
import Elites from "./elites/Elites";
import FastElites from "./elites/FastElites";

import "./index.css";

ReactDOM.render(
  <React.StrictMode>
    <HashRouter>
      <Routes>
        <Route path="/elites" element={<Elites />} />
        <Route path="/fastelites" element={<FastElites />} />
        <Route path="/" element={<App />} />
      </Routes>
    </HashRouter>
  </React.StrictMode>,
  document.getElementById("root")
);
