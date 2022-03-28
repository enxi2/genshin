import { Link } from "react-router-dom";

import styles from "./BackButton.module.scss";

export default function BackButton() {
  return (
    <Link to="/" className={styles.back}>
      Back to Genshin Index
    </Link>
  );
}
