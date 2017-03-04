function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6369\" class=\"headerLeftMenuInActive\"><a id=\"aID6369\" href=\"#\" OnMouseOver=\"link('_dir','picker0',this)\" class=\"leftMenuLinkHeadInActive\">picker</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID873\" class=\"leftMenuInActive\"><a id=\"aID873\" href=\"#\" OnMouseOver=\"link('_class','FramePicker54809',this)\" class=\"leftMenuLinkInActive\">FramePicker</a></div>\n");
document.write("<div id=\"divID874\" class=\"leftMenuInActive\"><a id=\"aID874\" href=\"#\" OnMouseOver=\"link('_class','FramePickerContext54809',this)\" class=\"leftMenuLinkInActive\">FramePickerContext</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
