import cx from "classnames";
import Panzoom, { PanzoomObject } from "@panzoom/panzoom";
import {
  createContext,
  HTMLAttributes,
  MouseEvent,
  useCallback,
  useContext,
  useEffect,
  useRef,
  useState,
} from "react";
import { useHotkeys } from "react-hotkeys-hook";

import style from "./Gallery.module.scss";

const NOP = () => {};

const GalleryContext = createContext<{
  preview: (src: string | null) => void;
}>({ preview: NOP });

function Preview(props: {
  src: string | null;
  close: () => void;
}): JSX.Element {
  const { src, close } = props;

  const image = useRef<HTMLImageElement>(null);
  const panzoom = useRef<PanzoomObject | null>(null);

  const preventDefault = useCallback((event: MouseEvent<HTMLImageElement>) => {
    event.preventDefault();
    event.stopPropagation();
  }, []);

  const resetPanzoom = useCallback(() => {
    if (src != null && image.current != null && panzoom.current != null) {
      const parent = image.current.parentElement;
      if (parent != null) {
        // Zoom so that the image is contained in the parent
        const iw = image.current.naturalWidth;
        const ih = image.current.naturalHeight;
        const imageAspect = iw / ih;
        const pw = parent.offsetWidth;
        const ph = parent.offsetHeight;
        const parentAspect = pw / ph;

        const zoom =
          imageAspect > parentAspect // wide or tall
            ? iw > pw
              ? pw / iw
              : 1
            : ih > ph
            ? ph / ih
            : 1;
        panzoom.current.zoom(zoom);
        panzoom.current.pan((pw - iw) / 2 / zoom, (ph - ih) / 2 / zoom);
      } else {
        panzoom.current.reset();
      }
    }
  }, [src]);

  useEffect(() => {
    if (image.current != null) {
      panzoom.current = Panzoom(image.current, {
        minScale: 0.1,
        maxScale: 2,
      });
      if (image.current.parentElement != null) {
        image.current.parentElement.addEventListener(
          "wheel",
          panzoom.current.zoomWithWheel
        );
      }
    }
  }, []);

  useHotkeys("escape", close);
  useHotkeys("0", resetPanzoom);

  return (
    <div
      className={cx(style.preview, src == null ? style.hidden : null)}
      onClick={close}
    >
      <img
        className={style.previewImage}
        src={src ?? ""}
        alt=""
        onClick={preventDefault}
        onLoad={resetPanzoom}
        ref={image}
      />
      <div className={style.close} onClick={close}>
        Close
      </div>
    </div>
  );
}

function Root(props: HTMLAttributes<HTMLDivElement>): JSX.Element {
  const { children, ...otherProps } = props;

  const [previewSrc, setPreviewSrc] = useState<string | null>(null);

  const preview = useCallback((src: string | null) => {
    setPreviewSrc(src);
  }, []);

  return (
    <div {...otherProps} className={style.root}>
      <GalleryContext.Provider
        value={{
          preview,
        }}
      >
        {children}
      </GalleryContext.Provider>
      <Preview src={previewSrc} close={() => preview(null)} />
    </div>
  );
}

function Title(props: HTMLAttributes<HTMLDivElement>): JSX.Element {
  const { children, ...otherProps } = props;

  return (
    <div className={style.title} {...otherProps}>
      {children}
    </div>
  );
}

function Image(props: { src: string }): JSX.Element {
  const { src } = props;

  const { preview } = useContext(GalleryContext);

  return (
    <img
      className={style.image}
      src={src}
      alt=""
      onClick={() => preview(src)}
    />
  );
}

function Text(props: HTMLAttributes<HTMLDivElement>): JSX.Element {
  const { children, ...otherProps } = props;

  return <div {...otherProps}>{children}</div>;
}

const Gallery = {
  Root,
  Title,
  Image,
  Text,
};

export default Gallery;
