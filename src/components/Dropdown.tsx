import {
  ChangeEvent,
  HTMLAttributes,
  useCallback,
  useEffect,
  useState,
} from "react";

export type Option<T extends string | number> = {
  label: string;
  value: T;
};

export default function Dropdown<T extends string | number>(
  props: {
    options: ReadonlyArray<Option<T>>;
    onSet?: (value: T) => void;
  } & HTMLAttributes<HTMLSelectElement>
): JSX.Element {
  const { options, onSet, ...otherProps } = props;

  const [selected, setSelected] = useState<number>(0);

  const handleChange = useCallback(
    (event: ChangeEvent<HTMLSelectElement>) => {
      if (onSet != null) {
        for (let i = 0; i < options.length; i++) {
          if (event.target.value === options[i].value.toString()) {
            setSelected(i);
            onSet(options[i].value);
            return;
          }
        }
      }
    },
    [options, onSet]
  );

  useEffect(() => {
    if (options.length > 0 && selected >= options.length) {
      setSelected(options.length - 1);
      if (onSet != null) {
        onSet(options[options.length - 1].value);
      }
    }
  }, [options, selected, onSet]);

  return (
    <select onChange={handleChange} {...otherProps}>
      {options.map((option) => {
        return (
          <option key={option.label} value={option.value}>
            {option.label}
          </option>
        );
      })}
    </select>
  );
}
