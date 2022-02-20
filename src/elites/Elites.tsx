import Gallery from "./Gallery";

import style from "./Elites.module.scss";

export default function Elites(): JSX.Element {
  return (
    <div className={style.container}>
      <Gallery.Root>
        <Gallery.Title>200 Elite / 1 Hour route</Gallery.Title>
        <Gallery.Text></Gallery.Text>
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Directions.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Dragonspine-ish.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Liyue-ish a.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Liyue-ish b.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Inazuma 600s200s a.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Inazuma 600s200s b.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Inazuma 600s200s c.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Enkanomiya 600s200s.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Enkanomiya Extra200s.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Inazuma Extra200s a.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Inazuma Extra200s b.jpg`}
        />
        <Gallery.Image
          src={`${process.env.PUBLIC_URL}/elites/Inazuma Extra200s c.jpg`}
        />
      </Gallery.Root>
    </div>
  );
}
