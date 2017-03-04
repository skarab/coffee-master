function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6367\" class=\"headerLeftMenuInActive\"><a id=\"aID6367\" href=\"#\" OnMouseOver=\"link('_dir','tone_mapper0',this)\" class=\"leftMenuLinkHeadInActive\">tone_mapper</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID871\" class=\"leftMenuInActive\"><a id=\"aID871\" href=\"#\" OnMouseOver=\"link('_class','FramePassToneMapper54809',this)\" class=\"leftMenuLinkInActive\">FramePassToneMapper</a></div>\n");
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
