function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6338\" class=\"headerLeftMenuInActive\"><a id=\"aID6338\" href=\"#\" OnMouseOver=\"link('_dir','audio0',this)\" class=\"leftMenuLinkHeadInActive\">audio</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6339\" class=\"leftMenuInActive\"><a id=\"aID6339\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6341\" class=\"leftMenuInActive\"><a id=\"aID6341\" href=\"#\" OnMouseOver=\"link('_dir','device/device0',this)\" class=\"leftMenuLinkInActive\">device</a></div>\n");
document.write("<div id=\"divID6343\" class=\"leftMenuInActive\"><a id=\"aID6343\" href=\"#\" OnMouseOver=\"link('_dir','sound/sound0',this)\" class=\"leftMenuLinkInActive\">sound</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID839\" class=\"leftMenuInActive\"><a id=\"aID839\" href=\"#\" OnMouseOver=\"link('_class','Module45182',this)\" class=\"leftMenuLinkInActive\">Module</a></div>\n");
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
