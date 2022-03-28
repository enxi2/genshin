import { Link } from "react-router-dom";

import styles from "./App.module.scss";

function App() {
  return (
    <div className={styles.container}>
      <h1>Genshin Stuff</h1>
      <Link to="/elites" className={styles.link}>
        2-hour Elite Cap
      </Link>
      <Link to="/fastelites" className={styles.link}>
        80-minute Elite Cap
      </Link>
      {/*
      <Link to="/wishstats" className={styles.link}>
        Wish Statistics
      </Link>
      */}
    </div>
  );
}

export default App;
